#pragma once
#include <sdk.hpp>

#include "./api.hpp"

static const UID OmpNodeComponent_UID = UID(0x8b256881a3704e81);
class IOmpNodeComponent : public IComponent
{
public:
	PROVIDE_UID(OmpNodeComponent_UID);

	// Do not use this function, it's only for internal usage. Use OMPNODE_API macro instead.
	virtual void createJSApi_UNSAFEINTERNAL(IOmpNodeAPI* api) = 0;

	// Do not use this function, it's only for internal usage.
	virtual void processV8ArgumentsIntoOmpNodeArgs_UNSAFEINTERNAL(void* V8Info, const OmpNodeAPIArgList& retArgList, OmpNodeAPIProcessor handler) = 0;

	// Do not use this function, it's only for internal usage. Use OMPNODE_CallEvent instead.
	virtual bool callEvent_UNSAFEINTERNAL(StringView eventName, bool waitForPromise, OmpNodeEventBadRet badRet, const OmpNodeEventArgList& retArgList) = 0;
};

class OmpNodeAPIManager
{
public:
	void Register(IOmpNodeAPI* api)
	{
		apiContainer.emplace(api);
	}

	void Initialize(IOmpNodeComponent* component)
	{
		if (component)
		{
			ompnode = component;
			for (auto api : apiContainer)
			{
				ompnode->createJSApi_UNSAFEINTERNAL(api);
			}
		}
	}

	IOmpNodeComponent* GetOmpNode()
	{
		return ompnode;
	}

	static OmpNodeAPIManager& Instance()
	{
		static OmpNodeAPIManager _Instance;
		return _Instance;
	}

private:
	IOmpNodeComponent* ompnode = nullptr;
	FlatHashSet<IOmpNodeAPI*> apiContainer;
};

// Call an event on JS side
// eventName - for event name, as a string
// badRet - the return value that causes your event chain to stop
// pass your arguments after this
template <typename... Args>
inline bool OMPNODE_CallEvent(StringView eventName, OmpNodeEventBadRet badRet, Args... args)
{
	Impl::DynamicArray<OmpNodeEventArg> list;
	int argIndex = 0;

	auto initializer = [&](auto& arg)
	{
		argIndex++;
		using T = std::decay_t<decltype(arg)>;
		if constexpr (std::is_same_v<T, int32_t> || std::is_same_v<T, int16_t> || std::is_same_v<T, int8_t>)
		{
			list.push_back({ int32_t(arg), OmpNodeEventArgType::Int32 });
		}
		else if constexpr (std::is_same_v<T, uint32_t> || std::is_same_v<T, uint16_t> || std::is_same_v<T, uint8_t>)
		{
			list.push_back({ uint32_t(arg), OmpNodeEventArgType::UInt32 });
		}
		else if constexpr (std::is_same_v<T, VoidPtr>)
		{
			list.push_back({ arg, OmpNodeEventArgType::Ptr });
		}
		else if constexpr (std::is_same_v<T, bool>)
		{
			list.push_back({ arg, OmpNodeEventArgType::Bool });
		}
		else if constexpr (std::is_same_v<T, float>)
		{
			list.push_back({ arg, OmpNodeEventArgType::Float });
		}
		else if constexpr (std::is_same_v<T, Impl::String>)
		{
			list.push_back({ arg, OmpNodeEventArgType::String });
		}
		else if constexpr (std::is_same_v<T, StringView>)
		{
			list.push_back({ arg.to_string(), OmpNodeEventArgType::String });
		}
		else if constexpr (std::is_same_v<T, const char*> || std::is_same_v<T, char*>)
		{
			list.push_back({ Impl::String(arg), OmpNodeEventArgType::String });
		}
		else
		{
			throw std::runtime_error(Impl::String("Unable to cast argument ") + std::to_string(argIndex) + "for event " + eventName.data());
		}
	};

	(initializer(args), ...);

	OmpNodeEventArgList argList = {
		list.size(),
		list.data()
	};

	return OmpNodeAPIManager::Instance().GetOmpNode()->callEvent_UNSAFEINTERNAL(eventName, true, badRet, argList);
}
