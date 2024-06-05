#include <sdk.hpp>

#include "runtime.hpp"

struct OmpNodeComponent final : IComponent {
	PROVIDE_UID(0x8b256881a3704e81);

	StringView componentName() const override {
		return "OmpNode";
	}

	SemanticVersion componentVersion() const override {
		return SemanticVersion(0, 0, 0, 0);
	}

	void onLoad(ICore* c) override {
		// Cache core, player pool here
		core = c;

		Log::Init(LogLevel::Debug);

		runtime = &Runtime::Instance();
		runtime->Init(c);

		c->printLn("OmpNode component loaded");
	}

	void onInit(IComponentList* components) override {
		// Cache components, add event handlers here

		// core->getEventDispatcher().addEventHandler(&ompnode::nodeImpl);
	}

	void provideConfiguration(ILogger& logger, IEarlyConfig& config, bool defaults) override {
		if (defaults) {
			config.setString("node_js.entry_file", "index.js");
		}
	}

	void onFree(IComponent* component) override {
	}

	void onReady() override {
		// Fire events here at earliest

		// TODO: use config
		ResourceInfo info;
		info.name = "Test Resource";
		info.entryFile = "./index.js";
		info.path = "./";
		info.configVersion = ConfigVersion::Version1;

		auto resource = runtime->CreateImpl(info);
		resource->Start();
	}

	void reset() override {
		free();
	}

	void free() override {
		delete this;
	}

	~OmpNodeComponent() {
		// Clean up what you did above
		if (core != nullptr) {
			// core->getEventDispatcher().removeEventHandler(&ompnode::nodeImpl);
			runtime->Dispose();
		}
	}

	ICore* core = nullptr;
	Runtime* runtime = nullptr;
};

COMPONENT_ENTRY_POINT() {
	return new OmpNodeComponent();
}
