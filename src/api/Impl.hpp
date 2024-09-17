#pragma once
#include "../runtime.hpp"

typedef void (*APIHandlerFunc_t)(const v8::FunctionCallbackInfo<v8::Value>& info);

class APIManager
{
public:
	void Register(const Impl::String& space, const Impl::String name, APIHandlerFunc_t func, bool thirdPartyAPI = false)
	{
		if (thirdPartyAPI)
		{
			thirdtPartyAPIContainer[space][name] = func;
		}
		else
		{
			apiContainer[space][name] = func;
		}
	}

	static APIManager& Instance()
	{
		static APIManager _Instance;
		return _Instance;
	}

	FlatHashMap<Impl::String, FlatHashMap<Impl::String, APIHandlerFunc_t>> apiContainer;
	FlatHashMap<Impl::String, FlatHashMap<Impl::String, APIHandlerFunc_t>> thirdtPartyAPIContainer;
};

class EventManager
{
public:
	void Register(const Impl::String name, EventCallback_Common func)
	{
		eventContainer[name] = func;
	}

	void Initialize(OMPAPI_t* ompapi)
	{
		for (auto event : eventContainer)
		{
			ompapi->Event.AddHandler(event.first.c_str(), EventPriorityType_FairlyHigh, event.second);
		}
	}

	static EventManager& Instance()
	{
		static EventManager _Instance;
		return _Instance;
	}

	FlatHashMap<Impl::String, EventCallback_Common> eventContainer;
};
