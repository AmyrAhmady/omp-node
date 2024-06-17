#pragma once

#include "common.hpp"
#include "ompcapi.h"

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

	const Impl::String& GetName()
	{
		return resource.name;
	}

	v8::Local<v8::Function> GetEventHandlerFunction()
	{
		return eventHandlerFunction.Get(isolate);
	}

	void SetEventHandlerFunction(v8::Local<v8::Function> function)
	{
		eventHandlerFunction.Reset(isolate, function);
	}

	bool CallEventHandler(const Impl::String& name, std::vector<v8::Local<v8::Value>>& args)
	{
		v8::Local<v8::Function> handler = GetEventHandlerFunction();
		auto returnValue = handler->Call(context.Get(isolate), v8::Undefined(isolate), args.size(), args.data());
		if (returnValue.IsEmpty())
		{
			return true;
		}
		else
		{
			return returnValue.ToLocalChecked()->BooleanValue(isolate);
		}
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
	node::async_context asyncContext {};
	helpers::CopyablePersistent<v8::Function> eventHandlerFunction;
};
