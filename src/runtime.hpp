#pragma once

#include "resource.hpp"

class Runtime
{
public:
	Runtime() = default;
	bool Init(ICore* c);

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

	std::vector<std::string> GetNodeArgs();
	void ProcessConfigOptions();

	node::MultiIsolatePlatform* GetPlatform() const
	{
		return platform.get();
	}

	FlatHashSet<Resource*> GetResources()
	{
		return resources;
	}

	Resource* GetResource(const std::string& name)
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

	static Runtime& Instance()
	{
		static Runtime _Instance;
		return _Instance;
	}

private:
	ICore* core = nullptr;

	v8::Isolate* isolate;
	helpers::CopyablePersistent<v8::Context> context;
	node::Environment* parentEnv;

	std::unique_ptr<node::MultiIsolatePlatform> platform;
	FlatHashSet<Resource*> resources;
};
