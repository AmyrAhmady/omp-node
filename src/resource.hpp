#pragma once

#include "common.hpp"

class Runtime;

class Resource
{
public:
	Resource(Runtime* _runtime, const ResourceInfo& _resource);

	Resource(const Resource&) = delete;

	bool Start();
	bool Stop();

	void Tick();

	void Started();

	node::Environment* GetEnv()
	{
		return env;
	}

	node::async_context GetAsyncContext()
	{
		return asyncContext;
	}

	v8::Local<v8::Object> GetAsyncResource()
	{
		return asyncResource.Get(isolate);
	}

	bool IsEnvStarted()
	{
		return envStarted;
	}

	inline v8::Isolate* GetIsolate()
	{
		return isolate;
	}

	inline v8::Local<v8::Context> GetContext()
	{
		return context.Get(isolate);
	}

	const std::string& GetName()
	{
		return resource.name;
	}

private:
	Runtime* runtime;

	bool envStarted = false;
	bool startError = false;
	ResourceInfo resource;

	v8::Isolate* isolate;
	helpers::CopyablePersistent<v8::Context> context;
	node::IsolateData* nodeData = nullptr;
	node::Environment* env = nullptr;
	uv_loop_t* uvLoop = nullptr;
	helpers::CopyablePersistent<v8::Object> asyncResource;
	node::async_context asyncContext{};
};
