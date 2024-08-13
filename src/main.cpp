#include <sdk.hpp>

#include "runtime.hpp"
#include "./api/Pools.hpp"

struct OmpNodeComponent final : IComponent, CoreEventHandler
{
	PROVIDE_UID(0x8b256881a3704e81);

	StringView componentName() const override
	{
		return "OmpNode";
	}

	SemanticVersion componentVersion() const override
	{
		return SemanticVersion(0, 0, 0, 0);
	}

	void onLoad(ICore* c) override
	{
		core = c;

		omp_initialize_capi(&ompapi);

		runtime = &Runtime::Instance();
		runtime->Init(c, &ompapi);

		c->printLn("OmpNode component loaded");
	}

	void onInit(IComponentList* components) override
	{
		NodeOmpPool::Instance().Init(core, components);
		NodeOmpPool::Instance().AddPoolEvents();
	}

	void provideConfiguration(ILogger& logger, IEarlyConfig& config, bool defaults) override
	{
		if (defaults)
		{
			config.setStrings("node.resources", Span<const StringView>());
			config.setStrings("node.cli_args", Span<const StringView>());

			// inspector
			config.setBool("node.inspector.enable", false);
			config.setInt("node.inspector.port", 9229);
			config.setString("node.inspector.host", "127.0.0.1");
			config.setBool("node.inspector.wait", false);
		}
		else
		{
			if (config.getType("node.resources") == ConfigOptionType_None)
			{
				config.setStrings("node.resources", Span<const StringView>());
			}

			if (config.getType("node.cli_args") == ConfigOptionType_None)
			{
				config.setStrings("node.cli_args", Span<const StringView>());
			}

			if (config.getType("node.inspector.enable") == ConfigOptionType_None)
			{
				config.setBool("node.inspector.enable", false);
			}

			if (config.getType("node.inspector.port") == ConfigOptionType_None)
			{
				config.setInt("node.inspector.port", 9229);
			}

			if (config.getType("node.inspector.host") == ConfigOptionType_None)
			{
				config.setString("node.inspector.host", "127.0.0.1");
			}

			if (config.getType("node.inspector.wait") == ConfigOptionType_None)
			{
				config.setBool("node.inspector.wait", false);
			}
		}
	}

	void onFree(IComponent* component) override
	{
	}

	void onReady() override
	{
		runtime->RunResources();
	}

	void onTick(Microseconds elapsed, TimePoint now) override
	{
		runtime->Tick();
		auto resources = *runtime->GetResources();
		for (auto resource : resources)
		{
			resource->Tick();
		}
	}

	void reset() override
	{
		free();
	}

	void free() override
	{
		delete this;
	}

	~OmpNodeComponent()
	{
		NodeOmpPool::Instance().RemovePoolEvents();
		if (core != nullptr)
		{
			runtime->Dispose();
		}
	}

	ICore* core = nullptr;
	Runtime* runtime = nullptr;
	OMPAPI_t ompapi;
};

COMPONENT_ENTRY_POINT()
{
	return new OmpNodeComponent();
}
