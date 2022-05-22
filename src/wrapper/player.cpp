#include "player.hpp"
#include "primitive.hpp"
#include "types.hpp"

IPlayer *JSToIPlayer(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(value.As<v8::Object>()->GetInternalField(0));

    return static_cast<IPlayer *>( pointer->Value());
}

WeaponSlotData JSToWeaponSlotData(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (!value->IsObject()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An object is required").ToLocalChecked()));
        return {};
    }

    auto idHandle = value.As<v8::Object>()->Get(context, StringViewToJS("id", context));
    auto ammoHandle = value.As<v8::Object>()->Get(context, StringViewToJS("ammo", context));

    if (idHandle.IsEmpty() || ammoHandle.IsEmpty()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An object doesn't have required fields").ToLocalChecked()));
        return {};
    }

    auto id = (uint8_t)JSToUInt(idHandle.ToLocalChecked(), context);
    auto ammo = (uint32_t)JSToUInt(ammoHandle.ToLocalChecked(), context);

    // todo: consider default and missing parameters

    return {
        id,
        ammo
    };
}

v8::Local<v8::Object> PlayerKeyDataToJS(PlayerKeyData &data, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    auto dataTemplate = v8::ObjectTemplate::New(context->GetIsolate());

    dataTemplate->Set(v8::String::NewFromUtf8(isolate, "keys").ToLocalChecked(),
                      v8::Integer::NewFromUnsigned(isolate, data.keys));
    dataTemplate->Set(v8::String::NewFromUtf8(isolate, "upDown").ToLocalChecked(),
                      v8::Integer::New(isolate, data.upDown));
    dataTemplate->Set(v8::String::NewFromUtf8(isolate, "leftRight").ToLocalChecked(),
                      v8::Integer::New(isolate, data.leftRight));

    auto object = dataTemplate->NewInstance(context).ToLocalChecked();

    return object;
}

v8::Local<v8::Object> PlayerBulletDataToJS(const PlayerBulletData &bulletData, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    auto dataTemplate = v8::ObjectTemplate::New(context->GetIsolate());

    auto object = dataTemplate->NewInstance(context).ToLocalChecked();

    object->Set(context,
                v8::String::NewFromUtf8(isolate, "origin").ToLocalChecked(),
                Vector3ToJS(bulletData.origin, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "hitPos").ToLocalChecked(),
                Vector3ToJS(bulletData.hitPos, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "offset").ToLocalChecked(),
                Vector3ToJS(bulletData.offset, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "weapon").ToLocalChecked(),
                UIntToJS(bulletData.weapon, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "hitType").ToLocalChecked(),
                UIntToJS(bulletData.hitType, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "hitID").ToLocalChecked(),
                UIntToJS(bulletData.hitID, context));

    // todo: add real checking (error handling)

    return object;
}

v8::Local<v8::Object> WeaponSlotDataToJS(const WeaponSlotData &slotData, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    auto dataTemplate = v8::ObjectTemplate::New(context->GetIsolate());

    auto object = dataTemplate->NewInstance(context).ToLocalChecked();

    object->Set(context,
                v8::String::NewFromUtf8(isolate, "id").ToLocalChecked(),
                UIntToJS(slotData.id, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "ammo").ToLocalChecked(),
                UIntToJS(slotData.ammo, context));

    // todo: add real checking (error handling)

    return object;
}


v8::Local<v8::Array> WeaponSlotsToJS(WeaponSlots slots, v8::Local<v8::Context> context) {
    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), slots.size());

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    for (int i = 0; i < slots.size(); i++) {
        array->Set(context, i, WeaponSlotDataToJS(slots[i], context));
    }

    return array;
}