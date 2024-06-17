#include <sdk.hpp>

#include "runtime.hpp"

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
		// Cache core, player pool here
		core = c;

		Log::Init(LogLevel::Debug);

		omp_initialize_capi(&ompapi);

		runtime = &Runtime::Instance();
		runtime->Init(c, &ompapi);

		c->printLn("OmpNode component loaded");
	}

	void onInit(IComponentList* components) override
	{
		// Cache components, add event handlers here
	}

	void provideConfiguration(ILogger& logger, IEarlyConfig& config, bool defaults) override
	{
		if (defaults)
		{
			config.setString("node_js.entry_file", "index.js");
		}
	}

	void onFree(IComponent* component) override
	{
	}

	void onReady() override
	{
		// Fire events here at earliest

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
		// Clean up what you did above
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
