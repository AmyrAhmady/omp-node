#include "vehicle.hpp"
#include "primitive.hpp"
#include "types.hpp"
#include "../wrapper/utils.hpp"

IVehicle *JSToIVehicle(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(value.As<v8::Object>()->GetInternalField(0));

    return static_cast<IVehicle *>( pointer->Value());
}

VehicleSpawnData JSToVehicleSpawnData(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (!value->IsObject()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An object is required").ToLocalChecked()));
        return {};
    }

    auto respawnDelayHandle = value.As<v8::Object>()->Get(context, StringViewToJS("respawnDelay", context));
    auto modelIDHandle = value.As<v8::Object>()->Get(context, StringViewToJS("modelID", context));
    auto positionHandle = value.As<v8::Object>()->Get(context, StringViewToJS("position", context));
    auto zRotationHandle = value.As<v8::Object>()->Get(context, StringViewToJS("zRotation", context));
    auto colour1Handle = value.As<v8::Object>()->Get(context, StringViewToJS("colour1", context));
    auto colour2Handle = value.As<v8::Object>()->Get(context, StringViewToJS("colour2", context));
    auto sirenHandle = value.As<v8::Object>()->Get(context, StringViewToJS("siren", context));
    auto interiorHandle = value.As<v8::Object>()->Get(context, StringViewToJS("interior", context));

    if (respawnDelayHandle.IsEmpty() || modelIDHandle.IsEmpty() || positionHandle.IsEmpty() || zRotationHandle.IsEmpty()
        || colour1Handle.IsEmpty() || colour2Handle.IsEmpty() || sirenHandle.IsEmpty() || interiorHandle.IsEmpty()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An object doesn't have required fields").ToLocalChecked()));
        return {};
    }

    auto respawnDelay = JSToSeconds(respawnDelayHandle.ToLocalChecked(), context);
    auto modelID = JSToInt(modelIDHandle.ToLocalChecked(), context);
    auto position = JSToVector3(positionHandle.ToLocalChecked(), context);
    auto zRotation = JSToFloat(zRotationHandle.ToLocalChecked(), context);
    auto colour1 = JSToInt(colour1Handle.ToLocalChecked(), context);
    auto colour2 = JSToInt(colour2Handle.ToLocalChecked(), context);
    auto siren = JSToBool(sirenHandle.ToLocalChecked(), context);
    auto interior = JSToInt(interiorHandle.ToLocalChecked(), context);

    // todo: consider default and missing parameters

    return {
        respawnDelay,
        modelID,
        position,
        zRotation,
        colour1,
        colour2,
        siren,
        interior
    };
}

VehicleParams JSToVehicleParams(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (!value->IsObject()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An object is required").ToLocalChecked()));
        return {};
    }

    auto engineHandle = value.As<v8::Object>()->Get(context, StringViewToJS("engine", context));
    auto lightsHandle = value.As<v8::Object>()->Get(context, StringViewToJS("lights", context));
    auto alarmHandle = value.As<v8::Object>()->Get(context, StringViewToJS("alarm", context));
    auto doorsHandle = value.As<v8::Object>()->Get(context, StringViewToJS("doors", context));
    auto bonnetHandle = value.As<v8::Object>()->Get(context, StringViewToJS("bonnet", context));
    auto bootHandle = value.As<v8::Object>()->Get(context, StringViewToJS("boot", context));
    auto objectiveHandle = value.As<v8::Object>()->Get(context, StringViewToJS("objective", context));
    auto sirenHandle = value.As<v8::Object>()->Get(context, StringViewToJS("siren", context));
    auto doorDriverHandle = value.As<v8::Object>()->Get(context, StringViewToJS("doorDriver", context));
    auto doorPassengerHandle = value.As<v8::Object>()->Get(context, StringViewToJS("doorPassenger", context));
    auto doorBackLeftHandle = value.As<v8::Object>()->Get(context, StringViewToJS("doorBackLeft", context));
    auto doorBackRightHandle = value.As<v8::Object>()->Get(context, StringViewToJS("doorBackRight", context));
    auto windowDriverHandle = value.As<v8::Object>()->Get(context, StringViewToJS("windowDriver", context));
    auto windowPassengerHandle = value.As<v8::Object>()->Get(context, StringViewToJS("windowPassenger", context));
    auto windowBackLeftHandle = value.As<v8::Object>()->Get(context, StringViewToJS("windowBackLeft", context));
    auto windowBackRightHandle = value.As<v8::Object>()->Get(context, StringViewToJS("windowBackRight", context));

    if (engineHandle.IsEmpty() || lightsHandle.IsEmpty() || alarmHandle.IsEmpty() || doorsHandle.IsEmpty()
        || bonnetHandle.IsEmpty() || bootHandle.IsEmpty() || objectiveHandle.IsEmpty() || sirenHandle.IsEmpty()
        || doorDriverHandle.IsEmpty() || doorPassengerHandle.IsEmpty() || doorBackLeftHandle.IsEmpty()
        || doorBackRightHandle.IsEmpty() || windowDriverHandle.IsEmpty() || windowPassengerHandle.IsEmpty()
        || windowBackLeftHandle.IsEmpty() || windowBackRightHandle.IsEmpty()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An object doesn't have required fields").ToLocalChecked()));
        return {};
    }

    int8_t engine = JSToInt(engineHandle.ToLocalChecked(), context);
    int8_t lights = JSToInt(lightsHandle.ToLocalChecked(), context);
    int8_t alarm = JSToInt(alarmHandle.ToLocalChecked(), context);
    int8_t doors = JSToInt(doorsHandle.ToLocalChecked(), context);
    int8_t bonnet = JSToInt(bonnetHandle.ToLocalChecked(), context);
    int8_t boot = JSToInt(bootHandle.ToLocalChecked(), context);
    int8_t objective = JSToInt(objectiveHandle.ToLocalChecked(), context);
    int8_t siren = JSToInt(sirenHandle.ToLocalChecked(), context);
    int8_t doorDriver = JSToInt(doorDriverHandle.ToLocalChecked(), context);
    int8_t doorPassenger = JSToInt(doorPassengerHandle.ToLocalChecked(), context);
    int8_t doorBackLeft = JSToInt(doorBackLeftHandle.ToLocalChecked(), context);
    int8_t doorBackRight = JSToInt(doorBackRightHandle.ToLocalChecked(), context);
    int8_t windowDriver = JSToInt(windowDriverHandle.ToLocalChecked(), context);
    int8_t windowPassenger = JSToInt(windowPassengerHandle.ToLocalChecked(), context);
    int8_t windowBackLeft = JSToInt(windowBackLeftHandle.ToLocalChecked(), context);
    int8_t windowBackRight = JSToInt(windowBackRightHandle.ToLocalChecked(), context);

    // todo: consider default and missing parameters

    return {
        engine,
        lights,
        alarm,
        doors,
        bonnet,
        boot,
        objective,
        siren,
        doorDriver,
        doorPassenger,
        doorBackLeft,
        doorBackRight,
        windowDriver,
        windowPassenger,
        windowBackLeft,
        windowBackRight,
    };
}

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

v8::Local<v8::Object> VehicleSpawnDataToJS(const VehicleSpawnData &data,
                                           v8::Local<v8::Context> context) { // todo: provide helper methods of the class to js somehow
    auto isolate = context->GetIsolate();

    auto dataTemplate = v8::ObjectTemplate::New(context->GetIsolate());

    auto object = dataTemplate->NewInstance(context).ToLocalChecked();

    object->Set(context,
                v8::String::NewFromUtf8(isolate, "respawnDelay").ToLocalChecked(),
                SecondsToJS(data.respawnDelay, context));
    object->Set(context, v8::String::NewFromUtf8(isolate, "modelID").ToLocalChecked(), IntToJS(data.modelID, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "position").ToLocalChecked(),
                Vector3ToJS(data.position, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "zRotation").ToLocalChecked(),
                FloatToJS(data.zRotation, context));
    object->Set(context, v8::String::NewFromUtf8(isolate, "colour1").ToLocalChecked(), IntToJS(data.colour1, context));
    object->Set(context, v8::String::NewFromUtf8(isolate, "colour2").ToLocalChecked(), IntToJS(data.colour2, context));
    object->Set(context, v8::String::NewFromUtf8(isolate, "siren").ToLocalChecked(), BoolToJS(data.siren, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "interior").ToLocalChecked(),
                IntToJS(data.interior, context));

    // todo: add real checking (error handling)

    return object;
}

v8::Local<v8::Object> VehicleParamsToJS(const VehicleParams &params,
                                        v8::Local<v8::Context> context) { // todo: provide helper methods of the class to js somehow
    auto isolate = context->GetIsolate();

    auto dataTemplate = v8::ObjectTemplate::New(context->GetIsolate());

    auto object = dataTemplate->NewInstance(context).ToLocalChecked();

    object->Set(context, v8::String::NewFromUtf8(isolate, "engine").ToLocalChecked(), IntToJS(params.engine, context));
    object->Set(context, v8::String::NewFromUtf8(isolate, "lights").ToLocalChecked(), IntToJS(params.lights, context));
    object->Set(context, v8::String::NewFromUtf8(isolate, "alarm").ToLocalChecked(), IntToJS(params.alarm, context));
    object->Set(context, v8::String::NewFromUtf8(isolate, "doors").ToLocalChecked(), IntToJS(params.doors, context));
    object->Set(context, v8::String::NewFromUtf8(isolate, "bonnet").ToLocalChecked(), IntToJS(params.bonnet, context));
    object->Set(context, v8::String::NewFromUtf8(isolate, "boot").ToLocalChecked(), IntToJS(params.boot, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "objective").ToLocalChecked(),
                IntToJS(params.objective, context));
    object->Set(context, v8::String::NewFromUtf8(isolate, "siren").ToLocalChecked(), IntToJS(params.siren, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "doorDriver").ToLocalChecked(),
                IntToJS(params.doorDriver, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "doorPassenger").ToLocalChecked(),
                IntToJS(params.doorPassenger, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "doorBackLeft").ToLocalChecked(),
                IntToJS(params.doorBackLeft, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "doorBackRight").ToLocalChecked(),
                IntToJS(params.doorBackRight, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "windowDriver").ToLocalChecked(),
                IntToJS(params.windowDriver, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "windowPassenger").ToLocalChecked(),
                IntToJS(params.windowPassenger, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "windowBackLeft").ToLocalChecked(),
                IntToJS(params.windowBackLeft, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "windowBackRight").ToLocalChecked(),
                IntToJS(params.windowBackRight, context));

    // todo: add real checking (error handling)

    return object;
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