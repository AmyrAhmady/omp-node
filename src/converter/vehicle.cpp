#include "vehicle.hpp"
#include "primitive.hpp"
#include "types.hpp"
#include "../wrapper/utils.hpp"

IVehicle *JSToIVehicle(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(value.As<v8::Object>()->GetInternalField(0));

    return static_cast<IVehicle *>( pointer->Value());
}

OBJECT_CONVERTER_DEFINE(
    VehicleSpawnData,
    (Seconds, respawnDelay, SecondsToJS, JSToSeconds),
    (int, modelID, IntToJS, JSToInt),
    (Vector3, position, Vector3ToJS, JSToVector3),
    (float, zRotation, FloatToJS, JSToFloat),
    (int, colour1, IntToJS, JSToInt),
    (int, colour2, IntToJS, JSToInt),
    (bool, siren, BoolToJS, JSToBool),
    (int, interior, IntToJS, JSToInt)
)

OBJECT_CONVERTER_DEFINE(
    VehicleParams,
    (int8_t, engine, Int8TToJS, JSToInt8T),
    (int8_t, lights, Int8TToJS, JSToInt8T),
    (int8_t, alarm, Int8TToJS, JSToInt8T),
    (int8_t, doors, Int8TToJS, JSToInt8T),
    (int8_t, bonnet, Int8TToJS, JSToInt8T),
    (int8_t, boot, Int8TToJS, JSToInt8T),
    (int8_t, objective, Int8TToJS, JSToInt8T),
    (int8_t, siren, Int8TToJS, JSToInt8T),
    (int8_t, doorDriver, Int8TToJS, JSToInt8T),
    (int8_t, doorPassenger, Int8TToJS, JSToInt8T),
    (int8_t, doorBackLeft, Int8TToJS, JSToInt8T),
    (int8_t, doorBackRight, Int8TToJS, JSToInt8T),
    (int8_t, windowDriver, Int8TToJS, JSToInt8T),
    (int8_t, windowPassenger, Int8TToJS, JSToInt8T),
    (int8_t, windowBackLeft, Int8TToJS, JSToInt8T),
    (int8_t, windowBackRight, Int8TToJS, JSToInt8T)
)

OBJECT_CONVERTER_DEFINE(
    UnoccupiedVehicleUpdate,
    (uint8_t, seat, UInt8TToJS, JSToUInt8T),
    (Vector3, position, Vector3ToJS, JSToVector3),
    (Vector3, velocity, Vector3ToJS, JSToVector3)
)

v8::Local<v8::Value> IVehicleToJS(IVehicle &vehicle, v8::Local<v8::Context> context) {
    auto ext = GetHandleStorageExtension(&vehicle);

    return ext->get();
}
v8::Local<v8::Value> IVehicleToJS(IVehicle *vehicle, v8::Local<v8::Context> context) {
    auto ext = GetHandleStorageExtension(vehicle);

    return ext->get();
}

v8::Local<v8::Array> CarriagesToJS(const StaticArray<IVehicle *, MAX_VEHICLE_CARRIAGES> &carriages,
                                   v8::Local<v8::Context> context) {
    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), carriages.size());

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    for (int i = 0; i < carriages.size(); i++) {
        array->Set(context, i, IVehicleToJS(carriages[i], context));
    }

    return array;
}

v8::Local<v8::Array> VehicleColourToJS(const Pair<int, int> &vehicleColour, v8::Local<v8::Context> context) {
    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), 2);

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    array->Set(context, 0, IntToJS(vehicleColour.first, context));
    array->Set(context, 1, IntToJS(vehicleColour.second, context));

    return array;
}