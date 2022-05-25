#include "pickup.hpp"
#include "primitive.hpp"
#include "types.hpp"
#include "../wrapper/utils.hpp"

IPickup *JSToIPickup(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(value.As<v8::Object>()->GetInternalField(0));

    return static_cast<IPickup *>(pointer->Value());
}

IPickup &JSToIPickupRef(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(value.As<v8::Object>()->GetInternalField(0));

    auto pointerValue = static_cast<IPickup *>(pointer->Value());

    return *pointerValue;
}

v8::Local<v8::Value> IPickupToJS(IPickup &pickup, v8::Local<v8::Context> context) {
    auto ext = GetHandleStorageExtension(&pickup);

    return ext->get();
}
v8::Local<v8::Value> IPickupToJS(IPickup *pickup, v8::Local<v8::Context> context) {
    auto ext = GetHandleStorageExtension(pickup);

    return ext->get();
}