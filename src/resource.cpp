#include "resource.hpp"
#include "nodeimpl.hpp"
#include "wrapper/utils.hpp"
#include "wrapper/vehicle/vehicle_pool_wrapper.hpp"
#include "wrapper/pickup/pickup_pool_wrapper.hpp"

v8::Isolate *GetV8Isolate() {
    return ompnode::nodeImpl.GetIsolate();
}

static v8::Platform *GetV8Platform() {
    return ompnode::nodeImpl.GetPlatform();
}

static node::IsolateData *GetNodeIsolate() {
    return ompnode::nodeImpl.GetNodeIsolate();
}

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

        L_DEBUG << 1;

        auto core = ompnode::nodeImpl.GetCore();
        WrapCore(core, _context);
        auto coreHandle = GetHandleStorageExtension(core)->get();

        _context->Global()->Set(_context,
                                v8::String::NewFromUtf8(GetV8Isolate(), "core").ToLocalChecked(),
                                coreHandle).Check();

        /**/
        auto componentList = ompnode::nodeImpl.GetComponentList();

        auto vehiclesComponent = componentList->queryComponent<IVehiclesComponent>();

        WrapVehiclePool(vehiclesComponent, _context);
        auto vehiclePoolHandle = GetHandleStorageExtension(vehiclesComponent)->get();

        _context->Global()->Set(_context,
                                v8::String::NewFromUtf8(GetV8Isolate(), "vehicles").ToLocalChecked(),
                                vehiclePoolHandle).Check();

        auto pickupsComponent = componentList->queryComponent<IPickupsComponent>();

        WrapPickupPool(pickupsComponent, _context);
        auto pickupPoolHandle = GetHandleStorageExtension(pickupsComponent)->get();

        _context->Global()->Set(_context,
                                v8::String::NewFromUtf8(GetV8Isolate(), "pickups").ToLocalChecked(),
                                pickupPoolHandle).Check();

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

