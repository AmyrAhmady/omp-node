#pragma once
#include "resource.hpp"

class Runtime
{
public:
	Runtime() = default;

	bool Init(ICore* c, OMPAPI_t* oapi);

	void Tick();

	void Dispose();

	void RunResources();

	Resource* CreateImpl(const ResourceInfo& resource);

	template <typename... Args>
	bool DispatchEvents(const Impl::String& name, bool waitForPromise, EventBadRet badRet, Args... args)
	{
		auto resources = *GetResources();
		bool result = true;
		for (auto resource : resources)
		{
			result = resource->DispatchEvent(name, waitForPromise, badRet, args...);
			switch (badRet)
			{
			case EventBadRet::False:
				if (!result)
				{
					return false;
				}
				break;
			case EventBadRet::True:
				if (result)
				{
					return true;
				}
				break;
			case EventBadRet::None:
			default:
				break;
			}
		}

		return result;
	}

	node::Environment* GetParentEnv() const
	{
		return parentEnv;
	}

	v8::Local<v8::Context> GetContext()
	{
		return context.Get(isolate);
	}

	void DestroyImpl(Resource* impl)
	{
		resources.erase(impl);
		delete impl;
	}

	node::MultiIsolatePlatform* GetPlatform() const
	{
		return platform.get();
	}

	FlatHashSet<Resource*>* GetResources()
	{
		return &resources;
	}

	Resource* GetResource(const Impl::String& name)
	{
		for (auto resource : resources)
		{
			if (resource->GetName() == name)
			{
				return resource;
			}
		}
		return nullptr;
	}

	ICore* GetCore()
	{
		return core;
	}

	OMPAPI_t* GetOMPAPI()
	{
		return ompapi;
	}

	static Runtime& Instance()
	{
		static Runtime _Instance;
		return _Instance;
	}

private:
	ICore* core = nullptr;
	OMPAPI_t* ompapi = nullptr;

	v8::Isolate* isolate;
	helpers::CopyablePersistent<v8::Context> context;
	node::Environment* parentEnv;
	std::unique_ptr<node::MultiIsolatePlatform> platform;
	FlatHashSet<Resource*> resources;
	std::vector<ResourceInfo> resourcesInfo;

	std::vector<Impl::String> GetNodeArgs();

	std::vector<StringView> GetResourcePathsFromconfig();
};
