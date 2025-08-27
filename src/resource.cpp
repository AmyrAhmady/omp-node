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
		auto startError = info[1]->BooleanValue(isolate);
		resource->Started(startError);
	}
}

static void OmpLogBridge(const v8::FunctionCallbackInfo<v8::Value>& info)
{
	v8::Isolate* isolate = info.GetIsolate();
	v8::Local<v8::Context> ctx = isolate->GetEnteredOrMicrotaskContext();
	if (ctx.IsEmpty())
	{
		ctx = isolate->GetCurrentContext();
	}

	if (ctx.IsEmpty())
	{
		auto core = Runtime::Instance().GetCore();
		if (core)
		{
			std::stringstream stream;
			stream << "[Unknown Resource] ";

			for (size_t i = 0; i < info.Length(); i++)
			{
				Impl::String arg = *v8::String::Utf8Value(isolate, info[i]);
				stream << arg;
				if (i != info.Length() - 1)
					stream << " ";
			}

			core->logLn(LogLevel::Message, "%s", stream.str().c_str());
		}
		return;
	}

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

static void SetOmpNodeLibraryFunction_(const v8::FunctionCallbackInfo<v8::Value>& info)
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
		resource->SetOmpNodeLibraryFunction(function.As<v8::Function>());
	}
}

Resource::Resource(Runtime* _runtime, const ResourceInfo& _resource)
	: resource(_resource)
	, runtime(_runtime)
	, isolate(_runtime->GetIsolate())
{
}

bool Resource::Start()
{
	v8::Locker locker(isolate);
	v8::Isolate::Scope isolateScope(isolate);
	v8::HandleScope handleScope(isolate);

	v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
	v8::Local<v8::Context> _context = node::NewContext(isolate, global);
	v8::Context::Scope scope(_context);

	_context->SetAlignedPointerInEmbedderData(1, this);
	context.Reset(isolate, _context);

	uvLoop = new uv_loop_t;
	uv_loop_init(uvLoop);

	nodeData = node::CreateIsolateData(isolate, uvLoop, runtime->GetPlatform());
	if (!nodeData)
	{
		return false;
	}

	std::vector<Impl::String> args { resource.entryFile };
	std::vector<Impl::String> execArgs {};
	node::EnvironmentFlags::Flags flags = (node::EnvironmentFlags::Flags)(node::EnvironmentFlags::kOwnsProcessState & node::EnvironmentFlags::kNoCreateInspector);

	env = node::CreateEnvironment(nodeData, _context, args, args, flags);

	v8::Local<v8::Object> resourceObj = v8::Object::New(isolate);
	resourceObj->Set(_context, v8::String::NewFromUtf8(isolate, "name").ToLocalChecked(), v8::String::NewFromUtf8(isolate, resource.name.c_str()).ToLocalChecked());
	resourceObj->Set(_context, v8::String::NewFromUtf8(isolate, "path").ToLocalChecked(), v8::String::NewFromUtf8(isolate, resource.path.c_str()).ToLocalChecked());
	resourceObj->Set(_context, v8::String::NewFromUtf8(isolate, "entryFile").ToLocalChecked(), v8::String::NewFromUtf8(isolate, resource.entryFile.c_str()).ToLocalChecked());

	auto inspectorConfig = Runtime::Instance().GetInspectorConfig();
	v8::Local<v8::Object> inspectorConfigObj = v8::Object::New(isolate);
	inspectorConfigObj->Set(_context, v8::String::NewFromUtf8(isolate, "enabled").ToLocalChecked(), v8::Boolean::New(isolate, inspectorConfig.enabled));
	inspectorConfigObj->Set(_context, v8::String::NewFromUtf8(isolate, "host").ToLocalChecked(), v8::String::NewFromUtf8(isolate, inspectorConfig.host.c_str()).ToLocalChecked());
	inspectorConfigObj->Set(_context, v8::String::NewFromUtf8(isolate, "port").ToLocalChecked(), v8::Int32::New(isolate, inspectorConfig.port));
	inspectorConfigObj->Set(_context, v8::String::NewFromUtf8(isolate, "wait").ToLocalChecked(), v8::Boolean::New(isolate, inspectorConfig.wait));

	v8::Local<v8::Object> internalOmpObj = v8::Object::New(isolate);
	for (auto group : APIManager::Instance().apiContainer)
	{
		v8::Local<v8::Object> groupObj = v8::Object::New(isolate);
		for (auto funcs : group.second)
		{
			groupObj->Set(_context, v8::String::NewFromUtf8(isolate, funcs.first.c_str()).ToLocalChecked(), v8::Function::New(_context, funcs.second).ToLocalChecked());
		}
		internalOmpObj->Set(_context, v8::String::NewFromUtf8(isolate, group.first.c_str()).ToLocalChecked(), groupObj);
	}

	for (auto group : APIManager::Instance().thirdtPartyAPIContainer)
	{
		v8::Local<v8::Object> groupObj = v8::Object::New(isolate);
		for (auto funcs : group.second)
		{
			groupObj->Set(_context, v8::String::NewFromUtf8(isolate, funcs.first.c_str()).ToLocalChecked(), v8::Function::New(_context, funcs.second).ToLocalChecked());
		}
		_context->Global()->Set(_context, v8::String::NewFromUtf8(isolate, group.first.c_str()).ToLocalChecked(), groupObj);
	}

	internalOmpObj->Set(_context, v8::String::NewFromUtf8(isolate, "voidSize").ToLocalChecked(), v8::Integer::New(isolate, sizeof(uintptr_t)));

	_context->Global()->Set(_context, v8::String::NewFromUtf8(isolate, "__internal_omp").ToLocalChecked(), internalOmpObj);

	_context->Global()->Set(_context, v8::String::NewFromUtf8(isolate, "__internal_resource").ToLocalChecked(), resourceObj);
	_context->Global()->Set(_context, v8::String::NewFromUtf8(isolate, "__internal_inspectorConfig").ToLocalChecked(), inspectorConfigObj);
	_context->Global()->Set(_context, v8::String::NewFromUtf8(isolate, "__internal_resourceLoaded").ToLocalChecked(), v8::Function::New(_context, &ResourceLoaded).ToLocalChecked());
	_context->Global()->Set(_context, v8::String::NewFromUtf8(isolate, "__internal_ompLogBridge").ToLocalChecked(), v8::Function::New(_context, &OmpLogBridge).ToLocalChecked());
	_context->Global()->Set(_context, v8::String::NewFromUtf8(isolate, "__internal_setEventHandlerFunction").ToLocalChecked(), v8::Function::New(_context, &SetEventHandlerFunction_).ToLocalChecked());
	_context->Global()->Set(_context, v8::String::NewFromUtf8(isolate, "__internal_setOmpNodeLibraryFunction").ToLocalChecked(), v8::Function::New(_context, &SetOmpNodeLibraryFunction_).ToLocalChecked());

	v8::Local<v8::Object> ompObj = v8::Object::New(isolate);
	_context->Global()->Set(_context, v8::String::NewFromUtf8(isolate, "__omp").ToLocalChecked(), ompObj);

	node::LoadEnvironment(env, bootstrap.c_str());

	asyncResource.Reset(isolate, v8::Object::New(isolate));
	asyncContext = node::EmitAsyncInit(isolate, asyncResource.Get(isolate), "OMPNodeResource");

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

	// Force microtask processing before and after UV loop
	isolate->PerformMicrotaskCheckpoint();
	runtime->GetPlatform()->DrainTasks(isolate);
	uv_run(uvLoop, UV_RUN_NOWAIT);
	isolate->PerformMicrotaskCheckpoint();
}

void Resource::CallOmpNodeLibraryInitializer()
{
	V8_ISOLATE_SCOPE(isolate);

	v8::Local<v8::Function> handler = GetOmpNodeLibraryFunction();

	if (handler.IsEmpty() || !handler->IsFunction() || !handler->IsCallable())
	{
		return;
	}

	std::vector<v8::Local<v8::Value>> args_;
	args_.push_back(helpers::JSValue(isolate, startError));

	auto retn = handler->Call(context.Get(isolate), v8::Undefined(isolate), args_.size(), args_.data());
	if (retn.IsEmpty())
	{
		return;
	}
	else
	{
		auto returnValue = retn.ToLocalChecked();
		if (returnValue->IsPromise())
		{
			v8::Local<v8::Promise> promise = returnValue.As<v8::Promise>();
			while (true)
			{
				v8::Promise::PromiseState state = promise->State();
				if (state == v8::Promise::PromiseState::kPending)
				{
					Runtime::Instance().Tick();
					// Run event loop
					Tick();
				}
				else if (state == v8::Promise::PromiseState::kFulfilled)
				{
					return;
				}
				else if (state == v8::Promise::PromiseState::kRejected)
				{
					return;
				}
			}
		}

		return;
	}
}

void Resource::TickRuntimeAndCurrentResource()
{
	Runtime::Instance().Tick();
	Tick();
}

bool Resource::DispatchEvent(const Impl::String& name, bool waitForPromise, OmpNodeEventBadRet badRet, const OmpNodeEventArgList& argList)
{
	V8_ISOLATE_SCOPE(isolate);

	v8::Local<v8::Function> handler = GetEventHandlerFunction();

	if ((name != "resourceStart" && startError) || handler.IsEmpty() || !handler->IsFunction() || !handler->IsCallable())
	{
		if (badRet == OmpNodeEventBadRet::None || badRet == OmpNodeEventBadRet::False)
		{
			return true;
		}
		return false;
	}

	std::vector<v8::Local<v8::Value>> args_;
	args_.push_back(helpers::JSValue(isolate, name));
	args_.push_back(helpers::JSValue(isolate, int(badRet)));

	for (int i = 0; i < argList.size; i++)
	{
		auto arg = argList.data[i];
		if (arg.type == OmpNodeEventArgType::Int32)
		{
			auto value = std::get<int32_t>(arg.value);
			args_.push_back(helpers::JSValue(isolate, value));
		}
		else if (arg.type == OmpNodeEventArgType::UInt32)
		{
			auto value = std::get<uint32_t>(arg.value);
			args_.push_back(helpers::JSValue(isolate, value));
		}
		else if (arg.type == OmpNodeEventArgType::Ptr)
		{
			auto value = std::get<VoidPtr>(arg.value);
			args_.push_back(helpers::JSValue(isolate, uintptr_t(value)));
		}
		else if (arg.type == OmpNodeEventArgType::String)
		{
			auto value = std::get<JSString>(arg.value);
			args_.push_back(helpers::JSValue(isolate, value));
		}
		else if (arg.type == OmpNodeEventArgType::Bool)
		{
			auto value = std::get<bool>(arg.value);
			args_.push_back(helpers::JSValue(isolate, value));
		}
		else if (arg.type == OmpNodeEventArgType::Float)
		{
			auto value = std::get<float>(arg.value);
			args_.push_back(helpers::JSValue(isolate, value));
		}
		else
		{
			helpers::Throw(isolate, ("Failed to convert value, this type conversion is not handled"));
			return false;
		}
	}

	auto retn = handler->Call(context.Get(isolate), v8::Undefined(isolate), args_.size(), args_.data());
	if (retn.IsEmpty())
	{
		return true;
	}
	else
	{
		auto returnValue = retn.ToLocalChecked();
		if (waitForPromise && returnValue->IsPromise())
		{
			v8::Local<v8::Promise> promise = returnValue.As<v8::Promise>();
			while (true)
			{
				v8::Promise::PromiseState state = promise->State();
				if (state == v8::Promise::PromiseState::kPending)
				{
					Runtime::Instance().Tick();
					// Run event loop
					Tick();
				}
				else if (state == v8::Promise::PromiseState::kFulfilled)
				{
					v8::Local<v8::Value> value = promise->Result();
					if (value->IsFalse())
					{
						return false;
					}

					return true;
				}
				else if (state == v8::Promise::PromiseState::kRejected)
				{
					// TODO: Do something about rejection in here
					return true;
				}
			}
		}

		return returnValue->BooleanValue(isolate);
	}
}
