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

	void Started(bool error);

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

	const Impl::String& GetPath()
	{
		return resource.path;
	}

	v8::Local<v8::Function> GetEventHandlerFunction()
	{
		return eventHandlerFunction.Get(isolate);
	}

	void SetEventHandlerFunction(v8::Local<v8::Function> function)
	{
		eventHandlerFunction.Reset(isolate, function);
	}

	v8::Local<v8::Function> GetOmpNodeLibraryFunction()
	{
		return ompNodeLibraryInitializerFunction.Get(isolate);
	}

	void SetOmpNodeLibraryFunction(v8::Local<v8::Function> function)
	{
		ompNodeLibraryInitializerFunction.Reset(isolate, function);
	}

	void CallOmpNodeLibraryInitializer();

	template <typename... Args>
	bool DispatchEvent(const Impl::String& name, bool waitForPromise, EventBadRet badRet, Args... args)
	{
		V8_ISOLATE_SCOPE(isolate);

		v8::Local<v8::Function> handler = GetEventHandlerFunction();

		if ((name != "resourceStart" && startError) || handler.IsEmpty() || !handler->IsFunction() || !handler->IsCallable())
		{
			if (badRet == EventBadRet::None || badRet == EventBadRet::False)
			{
				return true;
			}
			return false;
		}

		std::vector<v8::Local<v8::Value>> args_;
		args_.push_back(helpers::JSValue(isolate, name));
		args_.push_back(helpers::JSValue(isolate, int(badRet)));

		([&]
			{
				args_.push_back(helpers::JSValue(isolate, args));
			}(),
			...);

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

	void DispatchStartEvent(bool error)
	{
		DispatchEvent("resourceStart", true, EventBadRet::None, error);
		CallOmpNodeLibraryInitializer();
	}

	void DispatchStopEvent()
	{
		DispatchEvent("resourceStop", true, EventBadRet::None);
	}

	void DispatchErrorEvent(const Impl::String& errorMsg, const Impl::String& file, int32_t line, const Impl::String& stackTrace)
	{
		DispatchEvent("resourceError", true, EventBadRet::None, errorMsg, file, line, stackTrace);
	}

	static Resource* Get(v8::Local<v8::Context> ctx)
	{
		return static_cast<Resource*>(ctx->GetAlignedPointerFromEmbedderData(1));
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
	helpers::CopyablePersistent<v8::Function> ompNodeLibraryInitializerFunction;
};
