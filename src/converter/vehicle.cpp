#include "vehicle.hpp"
#include "primitive.hpp"
#include "types.hpp"
#include "../wrapper/utils.hpp"

IVehicle *JSToIVehicle(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(value.As<v8::Object>()->GetInternalField(0));

    return static_cast<IVehicle *>( pointer->Value());
}

IVehicle &JSToIVehicleRef(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(value.As<v8::Object>()->GetInternalField(0));

    auto pointerValue = static_cast<IVehicle *>( pointer->Value());

    return *pointerValue;
}

OBJECT_CONVERTER_DEFINE(VehicleSpawnData,
                        (Seconds, respawnDelay, SecondsToJS, JSToSeconds),
                        (int, modelID, IntToJS, JSToInt),
                        (Vector3, position, VectorToJS<Vector3>, JSToVector<Vector3>),
                        (float, zRotation, FloatToJS, JSToFloat),
                        (int, colour1, IntToJS, JSToInt),
                        (int, colour2, IntToJS, JSToInt),
                        (bool, siren, BoolToJS, JSToBool),
                        (int, interior, IntToJS, JSToInt))

OBJECT_CONVERTER_DEFINE(VehicleParams,
                        (int8_t, engine, IntToJS<int8_t>, JSToInt<int8_t>),
                        (int8_t, lights, IntToJS<int8_t>, JSToInt<int8_t>),
                        (int8_t, alarm, IntToJS<int8_t>, JSToInt<int8_t>),
                        (int8_t, doors, IntToJS<int8_t>, JSToInt<int8_t>),
                        (int8_t, bonnet, IntToJS<int8_t>, JSToInt<int8_t>),
                        (int8_t, boot, IntToJS<int8_t>, JSToInt<int8_t>),
                        (int8_t, objective, IntToJS<int8_t>, JSToInt<int8_t>),
                        (int8_t, siren, IntToJS<int8_t>, JSToInt<int8_t>),
                        (int8_t, doorDriver, IntToJS<int8_t>, JSToInt<int8_t>),
                        (int8_t, doorPassenger, IntToJS<int8_t>, JSToInt<int8_t>),
                        (int8_t, doorBackLeft, IntToJS<int8_t>, JSToInt<int8_t>),
                        (int8_t, doorBackRight, IntToJS<int8_t>, JSToInt<int8_t>),
                        (int8_t, windowDriver, IntToJS<int8_t>, JSToInt<int8_t>),
                        (int8_t, windowPassenger, IntToJS<int8_t>, JSToInt<int8_t>),
                        (int8_t, windowBackLeft, IntToJS<int8_t>, JSToInt<int8_t>),
                        (int8_t, windowBackRight, IntToJS<int8_t>, JSToInt<int8_t>))

OBJECT_CONVERTER_DEFINE(UnoccupiedVehicleUpdate,
                        (uint8_t, seat, UIntToJS<uint8_t>, JSToUInt<uint8_t>),
                        (Vector3, position, VectorToJS<Vector3>, JSToVector<Vector3>),
                        (Vector3, velocity, VectorToJS<Vector3>, JSToVector<Vector3>))

v8::Local<v8::Value> IVehicleToJS(IVehicle &vehicle, v8::Local<v8::Context> context) {
    auto ext = GetHandleStorageExtension(&vehicle);

    return ext->get();
}
v8::Local<v8::Value> IVehicleToJS(IVehicle *vehicle, v8::Local<v8::Context> context) {
    auto ext = GetHandleStorageExtension(vehicle);

    return ext->get();
}

v8::Local<v8::Array> VehicleCarriagesToJS(const VehicleCarriages &carriages, v8::Local<v8::Context> context) {
    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), carriages.size());

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    for (int i = 0; i < carriages.size(); i++) {
        array->Set(context, i, IVehicleToJS(carriages[i], context)).Check();
    }

    return array;
}

v8::Local<v8::Array> VehicleModelsToJS(const VehicleModels &models, v8::Local<v8::Context> context) {
    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), models.size());

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    for (int i = 0; i < models.size(); i++) {
        array->Set(context, i, UIntToJS(models[i], context)).Check();
    }

    return array;
}

v8::Local<v8::Array> VehicleColourToJS(const Pair<int, int> &vehicleColour, v8::Local<v8::Context> context) {
    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), 2);

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    array->Set(context, 0, IntToJS(vehicleColour.first, context)).Check();
    array->Set(context, 1, IntToJS(vehicleColour.second, context)).Check();

    return array;
}