#include <sdk.hpp>

#include "nodeimpl.hpp"

struct NodeJSComponent final : IComponent {
    PROVIDE_UID(0x8b256881a3704e81);

    StringView componentName() const override {
        return "NodeJS";
    }

    SemanticVersion componentVersion() const override {
        return SemanticVersion(0, 0, 0, 0);
    }

    void onLoad(ICore *c) override {
        // Cache core, player pool here
        core = c;

        Log::Init(LogLevel::Debug);

        ompnode::nodeImpl.Initialize(c);

        c->printLn("on load");
    }

    void onInit(IComponentList *components) override {
        // Cache components, add event handlers here

        ompnode::nodeImpl.SetComponentList(components);

        ompnode::nodeImpl.LoadResource("");

        core->getEventDispatcher().addEventHandler(&ompnode::nodeImpl);
    }

    void provideConfiguration(ILogger& logger, IEarlyConfig& config, bool defaults) override {
        if (defaults) {
            config.setString("node_js.entry_file", "index.js");
        }
    }

    void onFree(IComponent *component) override {
    }

    void onReady() override {
        // Fire events here at earliest
    }

    void reset() override {
        free();
    }

    void free() override {
        delete this;
    }

    ~NodeJSComponent() {
        // Clean up what you did above
        if (core != nullptr) {
            core->getEventDispatcher().removeEventHandler(&ompnode::nodeImpl);
            ompnode::nodeImpl.Stop();
        }
    }

    ICore *core = nullptr;
};

COMPONENT_ENTRY_POINT() {
    return new NodeJSComponent();
}
