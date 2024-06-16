#pragma once
#include "../runtime.hpp"

typedef void (*APIHandlerFunc_t)(const v8::FunctionCallbackInfo<v8::Value>& info);

class APIManager
{
public:
	void Register(const std::string& space, const std::string name, APIHandlerFunc_t func)
	{
		apiContainer[space][name] = func;
	}

	static APIManager& Instance()
	{
		static APIManager _Instance;
		return _Instance;
	}

	FlatHashMap<std::string, FlatHashMap<std::string, APIHandlerFunc_t>> apiContainer;
};
