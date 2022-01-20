#include <sdk.hpp>

#include "nodeimpl.hpp"

struct Main : IComponent, CoreEventHandler {
	PROVIDE_UUID(0x88f9172cc6eb78a3);

	StringView componentName() const override {
		return "Count vehicles in rules";
	}

	SemanticVersion componentVersion() const override {
		return SemanticVersion(0, 0, 0, 0);
	}

	void onTick(Microseconds elapsed, TimePoint now) override {
		ompnode::nodeImpl.Tick();
	}

	void onLoad(ICore* c) override {
		// Cache core, player pool here
		core = c;

		Log::Init(LogLevel::Debug);

		ompnode::nodeImpl.Initialize(c);

		c->printLn("on load");
	}

	void onInit(IComponentList* components) override {
		// Cache components, add event handlers here

		ompnode::nodeImpl.LoadResource("");

		core->getEventDispatcher().addEventHandler(this);

	}

	void onReady() override {
		// Fire events here at earliest
	}

	~Main() {
		// Clean up what you did above
		core->getEventDispatcher().removeEventHandler(this);
		ompnode::nodeImpl.Stop();
	}

	ICore* core = nullptr;
} component;

COMPONENT_ENTRY_POINT() {
	return &component;
}
