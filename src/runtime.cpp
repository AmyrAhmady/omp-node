#include "common.hpp"
#include "runtime.hpp"

bool Runtime::Init(ICore* c, OMPAPI_t* oapi)
{
	core = c;
	ompapi = oapi;

	ProcessConfigOptions();
	auto result = node::InitializeOncePerProcess(GetNodeArgs());

	if (result->early_return())
	{
		for (auto& error : result->errors())
		{
			L_ERROR << "Error while initializing node: " << error;
		}

		return false;
	}

	platform.reset(result->platform());

	auto allocator = node::CreateArrayBufferAllocator();
	isolate = node::NewIsolate(allocator, uv_default_loop(), platform.get());
	node::IsolateData* nodeData = node::CreateIsolateData(isolate, uv_default_loop(), platform.get(), allocator);

	// node::IsolateSettings is;
	// node::SetIsolateUpForNode(isolate, is);

	// IsWorker data slot
	// isolate->SetData(v8::Isolate::GetNumberOfDataSlots() - 1, new bool(false));

	{
		v8::Locker locker(isolate);
		v8::Isolate::Scope isolate_scope(isolate);
		v8::HandleScope handle_scope(isolate);

		context.Reset(isolate, node::NewContext(isolate));
		v8::Context::Scope scope(context.Get(isolate));

		parentEnv = node::CreateEnvironment(nodeData, context.Get(isolate), result->args(), result->exec_args());

		/*
			Load here only needs for debugging as this environment only used as a parent for real environments
		*/

		// node::LoadEnvironment(parentEnv, "console.log('PARENT INIT'); setInterval(() => {}, 1000);");
	}

	return true;
}

Resource* Runtime::CreateImpl(const ResourceInfo& resource)
{
	auto res = new Resource { this, resource };
	resources.insert(res);
	return res;
}

void Runtime::Tick()
{
	v8::Locker locker(isolate);
	v8::Isolate::Scope isolateScope(isolate);
	v8::HandleScope seal(isolate);
	v8::Context::Scope scope(context.Get(isolate));

	uv_run(uv_default_loop(), UV_RUN_NOWAIT);
	platform->DrainTasks(isolate);
}

void Runtime::Dispose()
{
	{
		v8::SealHandleScope seal(isolate);

		do
		{
			uv_run(uv_default_loop(), UV_RUN_DEFAULT);
			platform->DrainTasks(isolate);
		} while (uv_loop_alive(uv_default_loop()));
	}
	platform->UnregisterIsolate(isolate);
	isolate->Dispose();
	node::FreePlatform(platform.release());
	v8::V8::Dispose();
	v8::V8::ShutdownPlatform();
}

std::vector<Impl::String> Runtime::GetNodeArgs()
{
	// https://nodejs.org/docs/latest-v17.x/api/cli.html#options
	std::vector<Impl::String> args = { "omp-server", "--no-warnings", "--experimental-default-type=module" };

	return args;
}

void Runtime::ProcessConfigOptions()
{
}
