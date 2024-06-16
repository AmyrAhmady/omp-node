#pragma once

#include "resource.hpp"

class Runtime
{
public:
	Runtime() = default;
	bool Init(ICore* c, OMPAPI_t* oapi);

	node::Environment* GetParentEnv() const
	{
		return parentEnv;
	}

	v8::Local<v8::Context> GetContext()
	{
		return context.Get(isolate);
	}

	Resource* CreateImpl(const ResourceInfo& resource);

	void DestroyImpl(Resource* impl)
	{
		resources.erase(impl);
		delete impl;
	}

	void Tick();
	void Dispose();

	std::vector<Impl::String> GetNodeArgs();
	void ProcessConfigOptions();

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
};
