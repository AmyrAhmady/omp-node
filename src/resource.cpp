#include <sstream>

#include "common.hpp"
#include "resource.hpp"
#include "runtime.hpp"
#include "api/Impl.hpp"
#include "helpers/v8.hpp"

#include "bootstrap.hpp"

static void ResourceLoaded(const v8::FunctionCallbackInfo<v8::Value>& info)
{
	Impl::String resourceName;
	v8::Isolate* isolate = info.GetIsolate();
	v8::Local<v8::Context> ctx = isolate->GetEnteredOrMicrotaskContext();

	v8::MaybeLocal maybeVal = info[0]->ToString(ctx);
	if (maybeVal.IsEmpty())
		return;

	resourceName = *v8::String::Utf8Value(isolate, maybeVal.ToLocalChecked());

	auto foundResource = Runtime::Instance().GetResource(resourceName);
	auto resource = Resource::Get(ctx);
	if (resource && foundResource && resource->GetPath() == foundResource->GetPath())
	{
		auto startError = info[0]->BooleanValue(isolate);
		resource->Started(startError);
	}
}

static void OmpLogBridge(const v8::FunctionCallbackInfo<v8::Value>& info)
{
	v8::Isolate* isolate = info.GetIsolate();
	v8::Local<v8::Context> ctx = isolate->GetEnteredOrMicrotaskContext();

	auto resource = Resource::Get(ctx);
	auto core = Runtime::Instance().GetCore();
	if (core)
	{
		std::stringstream stream;
		stream << "[" << resource->GetName() << "] ";

		for (size_t i = 0; i < info.Length(); i++)
		{
			Impl::String arg = *v8::String::Utf8Value(isolate, info[i]);
			stream << arg;
			if (i != info.Length() - 1)
				stream << " ";
		}

		core->logLn(LogLevel::Message, "%s", stream.str().c_str());
	}
}

static void SetEventHandlerFunction_(const v8::FunctionCallbackInfo<v8::Value>& info)
{
	v8::Isolate* isolate = info.GetIsolate();
	v8::Local<v8::Context> ctx = isolate->GetEnteredOrMicrotaskContext();

	v8::MaybeLocal maybeVal = info[0]->ToString(ctx);
	if (maybeVal.IsEmpty())
		return;

	auto resource = Resource::Get(ctx);
	if (resource)
	{
		v8::Local<v8::Value> function = info[0];
		if (!function->IsFunction())
			return;
		resource->SetEventHandlerFunction(function.As<v8::Function>());
	}
}

Resource::Resource(Runtime* _runtime, const ResourceInfo& _resource)
	: resource(_resource)
	, runtime(_runtime)
{
	uvLoop = new uv_loop_t;
	uv_loop_init(uvLoop);

	auto allocator = node::CreateArrayBufferAllocator();
	auto platform = runtime->GetPlatform();
	isolate = node::NewIsolate(allocator, uvLoop, platform);
	nodeData = node::CreateIsolateData(isolate, uvLoop, runtime->GetPlatform(), allocator);

	v8::Locker locker(isolate);
	v8::Isolate::Scope isolateScope(isolate);
	v8::HandleScope handleScope(isolate);

	v8::Local<v8::Context> _context = node::NewContext(isolate);
	_context->SetAlignedPointerInEmbedderData(1, this);
	context.Reset(isolate, _context);
}

bool Resource::Start()
{
	v8::Locker locker(isolate);
	v8::Isolate::Scope isolateScope(isolate);
	v8::HandleScope handleScope(isolate);

	auto _context = GetContext();
	v8::Context::Scope scope(_context);

	v8::Local<v8::Object> resourceObj = v8::Object::New(isolate);
	resourceObj->Set(_context, v8::String::NewFromUtf8(isolate, "name").ToLocalChecked(), v8::String::NewFromUtf8(isolate, resource.name.c_str()).ToLocalChecked());
	resourceObj->Set(_context, v8::String::NewFromUtf8(isolate, "path").ToLocalChecked(), v8::String::NewFromUtf8(isolate, resource.path.c_str()).ToLocalChecked());
	resourceObj->Set(_context, v8::String::NewFromUtf8(isolate, "entryFile").ToLocalChecked(), v8::String::NewFromUtf8(isolate, resource.entryFile.c_str()).ToLocalChecked());

	v8::Local<v8::Object> ompObj = v8::Object::New(isolate);
	for (auto group : APIManager::Instance().apiContainer)
	{
		v8::Local<v8::Object> groupObj = v8::Object::New(isolate);
		for (auto funcs : group.second)
		{
			groupObj->Set(_context, v8::String::NewFromUtf8(isolate, funcs.first.c_str()).ToLocalChecked(), v8::Function::New(_context, funcs.second).ToLocalChecked());
		}
		ompObj->Set(_context, v8::String::NewFromUtf8(isolate, group.first.c_str()).ToLocalChecked(), groupObj);
	}
	_context->Global()->Set(_context, v8::String::NewFromUtf8(isolate, "__internal_omp").ToLocalChecked(), ompObj);

	_context->Global()->Set(_context, v8::String::NewFromUtf8(isolate, "__internal_resource").ToLocalChecked(), resourceObj);
	_context->Global()->Set(_context, v8::String::NewFromUtf8(isolate, "__internal_resourceLoaded").ToLocalChecked(), v8::Function::New(_context, &ResourceLoaded).ToLocalChecked());
	_context->Global()->Set(_context, v8::String::NewFromUtf8(isolate, "__internal_ompLogBridge").ToLocalChecked(), v8::Function::New(_context, &OmpLogBridge).ToLocalChecked());
	_context->Global()->Set(_context, v8::String::NewFromUtf8(isolate, "__internal_setEventHandlerFunction").ToLocalChecked(), v8::Function::New(_context, &SetEventHandlerFunction_).ToLocalChecked());

	node::ThreadId threadId = node::AllocateEnvironmentThreadId();
	auto flags = static_cast<node::EnvironmentFlags::Flags>(node::EnvironmentFlags::kNoFlags);
	auto inspector = node::GetInspectorParentHandle(runtime->GetParentEnv(), threadId, resource.entryFile.c_str());

	std::vector<Impl::String> args { resource.entryFile };
	std::vector<Impl::String> execArgs {};

	env = node::CreateEnvironment(nodeData, _context, args, execArgs, flags, threadId, std::move(inspector));

	node::LoadEnvironment(env, bootstrap.c_str());

	// Not sure it's needed anymore
	asyncResource.Reset(isolate, v8::Object::New(isolate));
	asyncContext = node::EmitAsyncInit(isolate, asyncResource.Get(isolate), "Resource");

	while (!envStarted && !startError)
	{
		runtime->Tick();
		Tick();
	}

	DispatchStartEvent(startError);

	return !startError;
}

bool Resource::Stop()
{
	v8::Locker locker(isolate);
	v8::Isolate::Scope isolateScope(isolate);
	v8::HandleScope handleScope(isolate);

	{
		v8::Context::Scope scope(GetContext());
		DispatchStopEvent();

		node::EmitAsyncDestroy(isolate, asyncContext);
		asyncResource.Reset();
	}

	node::EmitProcessBeforeExit(env);
	node::EmitProcessExit(env);

	context.Reset();

	node::Stop(env);

	node::FreeEnvironment(env);
	node::FreeIsolateData(nodeData);

	envStarted = false;

	uv_loop_close(uvLoop);
	delete uvLoop;

	return true;
}

void Resource::Started(bool error)
{
	envStarted = true;
	startError = error;
}
void Resource::Tick()
{
	v8::Locker locker(isolate);
	v8::Isolate::Scope isolateScope(isolate);
	v8::HandleScope handleScope(isolate);

	v8::Context::Scope scope(GetContext());
	node::CallbackScope callbackScope(isolate, asyncResource.Get(isolate), asyncContext);

	runtime->GetPlatform()->DrainTasks(isolate);
	uv_run(uvLoop, UV_RUN_NOWAIT);
}
