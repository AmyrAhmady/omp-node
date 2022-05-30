#include "resource.hpp"
#include "nodeimpl.hpp"
#include "wrapper/utils.hpp"
#include "wrapper/vehicle/vehicle_pool_wrapper.hpp"
#include "wrapper/pickup/pickup_pool_wrapper.hpp"
#include "wrapper/gangzone/gangzone_pool_wrapper.hpp"
#include "wrapper/checkpoint/checkpoint_pool_wrapper.hpp"
#include "wrapper/actor/actor_pool_wrapper.hpp"
#include "wrapper/dialog/dialog_pool_wrapper.hpp"
#include "wrapper/textlabel/textlabel_pool_wrapper.hpp"
#include "wrapper/object/object_pool_wrapper.hpp"
#include "wrapper/menu/menu_pool_wrapper.hpp"

v8::Isolate *GetV8Isolate() {
    return ompnode::nodeImpl.GetIsolate();
}

static v8::Platform *GetV8Platform() {
    return ompnode::nodeImpl.GetPlatform();
}

static node::IsolateData *GetNodeIsolate() {
    return ompnode::nodeImpl.GetNodeIsolate();
}

#define USE_WRAPPER(ComponentType, componentName, WrapperFunction) \
    auto componentName##Component = componentList->queryComponent<ComponentType>(); \
    WrapperFunction(componentName##Component, _context); \
    auto componentName##ComponentHandle = GetHandleStorageExtension(componentName##Component)->get(); \
    _context->Global()->Set(_context, \
        v8::String::NewFromUtf8(GetV8Isolate(), #componentName).ToLocalChecked(), \
        componentName##ComponentHandle).Check();

namespace ompnode {

    Resource::Resource(std::string name, std::string path)
        : name(std::move(name)), path(path), nodeEnvironment(nullptr, node::FreeEnvironment) {
    }

    Resource::~Resource() {
        Stop();
    }

    void Resource::Init(const std::string &entry) {
        std::string entryFile;
        std::vector<std::string> node_flags;

        L_DEBUG << "init :)";

        bool useInspector;

        if (!entry.empty()) {
            entryFile = entry;
            useInspector = false;
        } else {
            entryFile = "index.js";
            useInspector = false;
        }

        std::vector<std::string> args;
        args.emplace_back("node");

        for (auto &flag: node_flags) {
            args.emplace_back(flag.c_str());
        }

        args.emplace_back(entryFile.c_str());

        for (auto &flag: args) {
            L_DEBUG << "node flags: " << flag;
        }

        std::vector<std::string> exec_args;

        v8::Locker locker(GetV8Isolate());
        v8::Isolate::Scope isolateScope(GetV8Isolate());
        v8::HandleScope handleScope(GetV8Isolate());

        v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(GetV8Isolate());

        // create a global variable for resource
        v8val::add_definition("__resname", name, global);

        v8::Local<v8::Context> _context = node::NewContext(GetV8Isolate(), global);
        context.Reset(GetV8Isolate(), _context);
        v8::Context::Scope scope(_context);

        auto core = ompnode::nodeImpl.GetCore();
        WrapCore(core, _context);
        auto coreHandle = GetHandleStorageExtension(core)->get();

        _context->Global()->Set(_context,
                                v8::String::NewFromUtf8(GetV8Isolate(), "core").ToLocalChecked(),
                                coreHandle).Check();

        /**/
        auto componentList = ompnode::nodeImpl.GetComponentList();

        USE_WRAPPER(IVehiclesComponent, vehicles, WrapVehiclePool)
        USE_WRAPPER(IPickupsComponent, pickups, WrapPickupPool)
        USE_WRAPPER(IGangZonesComponent, gangZones, WrapGangZonePool)
        USE_WRAPPER(ICheckpointsComponent, checkpoints, WrapCheckpointPool)
        USE_WRAPPER(IActorsComponent, actors, WrapActorPool)
        USE_WRAPPER(IDialogsComponent, dialogs, WrapDialogPool)
        USE_WRAPPER(ITextLabelsComponent, textLabels, WrapTextLabelPool)
        USE_WRAPPER(IObjectsComponent, objects, WrapObjectPool)
        USE_WRAPPER(IMenusComponent, menus, WrapMenuPool)

        node::EnvironmentFlags::Flags flags = node::EnvironmentFlags::kOwnsProcessState;

        if (useInspector) {
            flags = static_cast<node::EnvironmentFlags::Flags>(flags | node::EnvironmentFlags::kOwnsInspector);
        }

        auto env = node::CreateEnvironment(GetNodeIsolate(), _context, args, exec_args, flags, {});

        node::LoadEnvironment(env, node::StartExecutionCallback{});

        nodeEnvironment.reset(env);

        return;
    }

    void Resource::Stop() {
        node::Stop(nodeEnvironment.get());
        node::FreeEnvironment(nodeEnvironment.get());
        context.Reset();
    }

    void v8val::add_definition(const std::string &name,
                               const std::string &value,
                               v8::Local<v8::ObjectTemplate> &global) {
        v8::Local<v8::Value> test = v8::String::NewFromUtf8(GetV8Isolate(),
                                                            value.c_str(),
                                                            v8::NewStringType::kNormal,
                                                            static_cast<int>(value.length())).ToLocalChecked();
        global->Set(v8::String::NewFromUtf8(GetV8Isolate(), name.c_str(), v8::NewStringType::kNormal).ToLocalChecked(),
                    test,
                    v8::PropertyAttribute(v8::ReadOnly | v8::DontDelete));
    }
}

