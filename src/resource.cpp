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
#include "wrapper/textdraw/textdraw_pool_wrapper.hpp"
#include "wrapper/class/class_pool_wrapper.hpp"
#include "wrapper/variable/variable_component_wrapper.hpp"

#include "wrapper/entity/id_provider_wrapper.hpp"
#include "wrapper/entity/entity_wrapper.hpp"
#include "wrapper/actor/actor_wrapper.hpp"
#include "wrapper/class/class_wrapper.hpp"
#include "wrapper/gangzone/gangzone_wrapper.hpp"
#include "wrapper/menu/menu_wrapper.hpp"
#include "wrapper/object/object_base_wrapper.hpp"
#include "wrapper/object/object_wrapper.hpp"
#include "wrapper/object/player_object_wrapper.hpp"
#include "wrapper/pickup/pickup_wrapper.hpp"
#include "wrapper/textdraw/textdraw_base_wrapper.hpp"
#include "wrapper/textdraw/textdraw_wrapper.hpp"
#include "wrapper/textdraw/player_textdraw_wrapper.hpp"
#include "wrapper/textlabel/textlabel_base_wrapper.hpp"
#include "wrapper/textlabel/textlabel_wrapper.hpp"
#include "wrapper/textlabel/player_textlabel_wrapper.hpp"

#include "wrapper/checkpoint/player_checkpoint_data_wrapper.hpp"
#include "wrapper/class/player_class_data_wrapper.hpp"
#include "wrapper/dialog/player_dialog_data_wrapper.hpp"
#include "wrapper/menu/player_menu_data_wrapper.hpp"
#include "wrapper/object/player_object_data_wrapper.hpp"
#include "wrapper/textdraw/player_textdraw_data_wrapper.hpp"
#include "wrapper/textlabel/player_textlabel_data_wrapper.hpp"
#include "wrapper/variable/player_variable_data_wrapper.hpp"
#include "wrapper/vehicle/player_vehicle_data_wrapper.hpp"

#include "wrapper/vehicle/vehicle_wrapper.hpp"
#include "wrapper/player/player_wrapper.hpp"

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

#define ADD_CONSTRUCTOR_TEMPLATE(ComponentType) \
    auto constructorOf##ComponentType = wrapper##_##ComponentType::Wrapped_CreateConstructorTemplate(isolate); \
    global->Set(isolate, #ComponentType, constructorOf##ComponentType);

#define INHERIT_CONSTRUCTOR(ComponentType) constructorOf##ComponentType

#define ADD_CONSTRUCTOR_TEMPLATE_INHERIT(ComponentType, ...) \
    auto constructorOf##ComponentType = wrapper##_##ComponentType::Wrapped_CreateConstructorTemplate(isolate, FOR_EACH(INHERIT_CONSTRUCTOR, ##__VA_ARGS__)); \
    global->Set(isolate, #ComponentType, constructorOf##ComponentType);

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
            entryFile = "dist-omp/index.js";
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

        auto isolate = GetV8Isolate();

        ADD_CONSTRUCTOR_TEMPLATE(IIDProvider)
        ADD_CONSTRUCTOR_TEMPLATE_INHERIT(IEntity, IIDProvider)

        ADD_CONSTRUCTOR_TEMPLATE_INHERIT(IActor, IEntity)

        ADD_CONSTRUCTOR_TEMPLATE_INHERIT(IClass, IIDProvider)
        ADD_CONSTRUCTOR_TEMPLATE_INHERIT(IGangZone, IIDProvider)
        ADD_CONSTRUCTOR_TEMPLATE_INHERIT(IMenu, IIDProvider)

        ADD_CONSTRUCTOR_TEMPLATE_INHERIT(IBaseObject, IEntity)
        ADD_CONSTRUCTOR_TEMPLATE_INHERIT(IObject, IBaseObject)
        ADD_CONSTRUCTOR_TEMPLATE_INHERIT(IPlayerObject, IBaseObject)

        ADD_CONSTRUCTOR_TEMPLATE_INHERIT(IPickup, IEntity)

        ADD_CONSTRUCTOR_TEMPLATE_INHERIT(ITextDrawBase, IIDProvider)
        ADD_CONSTRUCTOR_TEMPLATE_INHERIT(ITextDraw, ITextDrawBase)
        ADD_CONSTRUCTOR_TEMPLATE_INHERIT(IPlayerTextDraw, ITextDrawBase)

        ADD_CONSTRUCTOR_TEMPLATE_INHERIT(ITextLabelBase, IEntity)
        ADD_CONSTRUCTOR_TEMPLATE_INHERIT(ITextLabel, IEntity)
        ADD_CONSTRUCTOR_TEMPLATE_INHERIT(IPlayerTextLabel, IEntity)

        ADD_CONSTRUCTOR_TEMPLATE_INHERIT(IVehicle, IEntity)
        ADD_CONSTRUCTOR_TEMPLATE_INHERIT(IPlayer, IEntity)

        ADD_CONSTRUCTOR_TEMPLATE(IPlayerCheckpointData)
        ADD_CONSTRUCTOR_TEMPLATE(IPlayerClassData)
        ADD_CONSTRUCTOR_TEMPLATE(IPlayerDialogData)
        ADD_CONSTRUCTOR_TEMPLATE(IPlayerMenuData)
        ADD_CONSTRUCTOR_TEMPLATE(IPlayerObjectData)
        ADD_CONSTRUCTOR_TEMPLATE(IPlayerTextDrawData)
        ADD_CONSTRUCTOR_TEMPLATE(IPlayerTextLabelData)
        ADD_CONSTRUCTOR_TEMPLATE(IPlayerVariableData)
        ADD_CONSTRUCTOR_TEMPLATE(IPlayerVehicleData)

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
        USE_WRAPPER(ITextDrawsComponent, textDraws, WrapTextDrawPool)
        USE_WRAPPER(IClassesComponent, classes, WrapClassPool)
        USE_WRAPPER(IVariablesComponent, variables, WrapVariableComponent)

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

