#pragma once
#include "resource.hpp"

class Runtime
{
	struct InspectorConfig
	{
		bool enabled;
		Impl::String host;
		int port;
		bool wait;
	};

public:
	Runtime() = default;

	bool Init(ICore* c, OMPAPI_t* oapi);

	void Tick();

	void Dispose();

	void RunResources();

	Resource* CreateImpl(const ResourceInfo& resource);

	template <typename... Args>
	bool DispatchEvents(const Impl::String& name, bool waitForPromise, OmpNodeEventBadRet badRet, Args... args)
	{
		auto resources = *GetResources();
		bool result = true;
		for (auto resource : resources)
		{
			result = resource->DispatchEvent(name, waitForPromise, badRet, args...);
			switch (badRet)
			{
			case OmpNodeEventBadRet::False:
				if (!result)
				{
					return false;
				}
				break;
			case OmpNodeEventBadRet::True:
				if (result)
				{
					return true;
				}
				break;
			case OmpNodeEventBadRet::None:
			default:
				break;
			}
		}

		return result;
	}

	bool DispatchEvents(const Impl::String& name, bool waitForPromise, OmpNodeEventBadRet badRet, const OmpNodeEventArgList& argList)
	{
		auto resources = *GetResources();
		bool result = true;
		for (auto resource : resources)
		{
			result = resource->DispatchEvent(name, waitForPromise, badRet, argList);
			switch (badRet)
			{
			case OmpNodeEventBadRet::False:
				if (!result)
				{
					return false;
				}
				break;
			case OmpNodeEventBadRet::True:
				if (result)
				{
					return true;
				}
				break;
			case OmpNodeEventBadRet::None:
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

	v8::Isolate* GetIsolate() const
	{
		return isolate;
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

	InspectorConfig GetInspectorConfig() const
	{
		return inspectorConfig;
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
	InspectorConfig inspectorConfig;

	std::vector<Impl::String> GetNodeArgs();

	void StoreExtraNodeConfig();

	std::vector<StringView> GetResourcePathsFromconfig();
};
