#include "../../logger.hpp"
#include "vehicle_pool_wrapper.hpp"
#include "vehicle_wrapper.hpp"
#include "../primitive.hpp"
#include "../types.hpp"

IVehicle* create(bool isStatic, int modelID, Vector3 position, float Z = 0.0f, int colour1 = -1, int colour2 = -1, Seconds respawnDelay = Seconds(-1), bool addSiren = false);

void create(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto vehiclePool = GetContextExternalPointer<IVehiclesComponent>(info);

    auto isStatic = JSToBool(info[0], context);
    auto modelId = JSToInt(info[1], context);
    auto position = JSToVector3(info[2], context);
    auto z = JSToFloat(info[3], context);
    auto col1 = JSToInt(info[4], context);
    auto col2 = JSToInt(info[5], context);
    Seconds respawnDelay(JSToInt(info[6], context));
    auto addSiren = JSToBool(info[7], context);

    auto vehicle = vehiclePool->create(isStatic, modelId, position, z, col1, col2, respawnDelay, addSiren);

    auto vehicleHandle = GetHandleStorageExtension(vehicle)->get();

    info.GetReturnValue().Set(vehicleHandle);
}



struct VehicleEntryHandler : PoolEventHandler<IVehicle> {
    v8::Isolate *isolate;
    v8::UniquePersistent<v8::Context> context;

    VehicleEntryHandler(v8::Local<v8::Context> _context)
        : isolate(_context->GetIsolate()), context(_context->GetIsolate(), _context) {
    }

    /// Called right after a new entry was constructed
    void onPoolEntryCreated(IVehicle &entry) override {
        L_DEBUG << "onPoolEntryCreated";
        v8::Locker locker(isolate);
        v8::Isolate::Scope isolateScope(isolate);

        v8::HandleScope scope(isolate);

        auto _context = context.Get(isolate);

        v8::Context::Scope contextScope(_context);

        WrapVehicle(&entry, _context);
    };

    /// Called just before an entry is destructed
    void onPoolEntryDestroyed(IVehicle &entry) override {
        v8::Locker locker(isolate);
        v8::Isolate::Scope isolateScope(isolate);

        v8::HandleScope scope(isolate);

        auto _context = context.Get(isolate);

        v8::Context::Scope contextScope(_context);

        auto handleStorage = GetHandleStorageExtension(&entry);

        if (handleStorage != nullptr) {
            auto entryHandle = handleStorage->get();

            entryHandle.As<v8::Object>()->SetInternalField(0, v8::External::New(isolate, nullptr));
        }
    };
};

VehicleEntryHandler *handler;

void WrapVehiclePool(IVehiclesComponent *vehiclePool, v8::Local<v8::Context> context) {
    handler = new VehicleEntryHandler(context); // todo: store somewhere to delete later

    vehiclePool->getPoolEventDispatcher().addEventHandler(handler);

    ObjectMethods methods = {{
                                 "create",
                                 create
                             },
    };

    auto vehiclePoolHandle = InterfaceToObject(vehiclePool, context, methods);

    vehiclePool->addExtension(new IHandleStorage(context->GetIsolate(), vehiclePoolHandle), true);
}