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
