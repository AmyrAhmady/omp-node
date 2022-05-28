#include "gangzone.hpp"
#include "primitive.hpp"
#include "types.hpp"
#include "../wrapper/utils.hpp"

OBJECT_CONVERTER_DEFINE(GangZonePos,
                        (Vector2, min, VectorToJS<Vector2>, JSToVector<Vector2>),
                        (Vector2, max, VectorToJS<Vector2>, JSToVector<Vector2>))

IGangZone *JSToIGangZone(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(value.As<v8::Object>()->GetInternalField(0));

    return static_cast<IGangZone *>(pointer->Value());
}

IGangZone &JSToIGangZoneRef(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(value.As<v8::Object>()->GetInternalField(0));

    auto pointerValue = static_cast<IGangZone *>(pointer->Value());

    return *pointerValue;
}

v8::Local<v8::Value> IGangZoneToJS(IGangZone &gangZone, v8::Local<v8::Context> context) {
    auto ext = GetHandleStorageExtension(&gangZone);

    return ext->get();
}
v8::Local<v8::Value> IGangZoneToJS(IGangZone *gangZone, v8::Local<v8::Context> context) {
    if (gangZone == nullptr) {
        return v8::Null(context->GetIsolate());
    }

    auto ext = GetHandleStorageExtension(gangZone);

    return ext->get();
}

v8::Local<v8::Array> FlatPtrHashSetIGangZoneToJS(const FlatPtrHashSetIGangZone &gangZones, v8::Local<v8::Context> context) {
    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), gangZones.size());

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    int i = 0;
    for (auto gangZone: gangZones) {
        array->Set(context, i++, IGangZoneToJS(*gangZone, context)).Check();
    }

    return array;
}