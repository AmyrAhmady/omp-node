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

	void TickRuntimeAndCurrentResource();

	template <typename... Args>
	bool DispatchEvent(const Impl::String& name, bool waitForPromise, OmpNodeEventBadRet badRet, Args... args)
	{
		V8_ISOLATE_SCOPE(isolate);

		if (!isolate)
		{
			// runtime->GetCore()->logLn(LogLevel::Warning, "ERROR: Isolate is null for event %s\n", name.c_str());
			return false;
		}

		v8::Context::Scope context_scope(context.Get(isolate));

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

		(args_.push_back(helpers::JSValue(isolate, args)), ...);

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
				v8::Promise::PromiseState initialState = promise->State();

				int loopCount = 0;
				const int maxLoops = 50000;
				while (true)
				{
					v8::Promise::PromiseState state = promise->State();
					if (state == v8::Promise::PromiseState::kPending)
					{
						loopCount++;
						if (loopCount % 1000 == 0)
						{
							// runtime->GetCore()->logLn(LogLevel::Warning, "DispatchEvent( name = %s ) - Still waiting for promise (loop %d)...\n", name.c_str(), loopCount);
						}

						// Timeout mechanism
						if (loopCount > maxLoops)
						{
							// runtime->GetCore()->logLn(LogLevel::Warning, "DispatchEvent( name = %s ) - TIMEOUT: Promise did not resolve after %d loops. Returning true.\n", name.c_str(), maxLoops);
							return true;
						}

						// Run event loop
						TickRuntimeAndCurrentResource();
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

	bool DispatchEvent(const Impl::String& name, bool waitForPromise, OmpNodeEventBadRet badRet, const OmpNodeEventArgList& argList);

	void DispatchStartEvent(bool error)
	{
		DispatchEvent("resourceStart", true, OmpNodeEventBadRet::None, error);
		CallOmpNodeLibraryInitializer();
	}

	void DispatchStopEvent()
	{
		DispatchEvent("resourceStop", true, OmpNodeEventBadRet::None);
	}

	void DispatchErrorEvent(const Impl::String& errorMsg, const Impl::String& file, int32_t line, const Impl::String& stackTrace)
	{
		DispatchEvent("resourceError", true, OmpNodeEventBadRet::None, errorMsg, file, line, stackTrace);
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
