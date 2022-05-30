#include "player.hpp"
#include "primitive.hpp"
#include "types.hpp"
#include "../wrapper/utils.hpp"
#include "entity.hpp"

v8::Local<v8::Array> FlatPtrHashSetIPlayerToJS(const FlatPtrHashSet<IPlayer> &players, v8::Local<v8::Context> context) {
    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), players.size());

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    int i = 0;
    for (auto player: players) {
        array->Set(context, i++, EntityToJS<IPlayer>(*player, context)).Check();
    }

    return array;
}

v8::Local<v8::Array> WeaponSlotsToJS(const WeaponSlots &slots, v8::Local<v8::Context> context) {
    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), slots.size());

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    for (int i = 0; i < slots.size(); i++) {
        array->Set(context, i, WeaponSlotDataToJS(slots[i], context)).Check();
    }

    return array;
}

v8::Local<v8::Array> SkillLevelsToJS(const StaticArray<uint16_t, NUM_SKILL_LEVELS> &skills,
                                     v8::Local<v8::Context> context) {
    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), skills.size());

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    for (int i = 0; i < skills.size(); i++) {
        array->Set(context, i, UIntToJS(skills[i], context)).Check();
    }

    return array;
}

WeaponSlots JSToWeaponSlots(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (!value->IsArray()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An array is required").ToLocalChecked()));
        return {};
    }

    auto slots = value.As<v8::Array>();

    WeaponSlots weaponSlots;

    for (int i = 0; i < weaponSlots.size(); i++) {
        auto value = JSToWeaponSlotData(slots->Get(context, i).ToLocalChecked(), context);

        weaponSlots[i] = value;
    }

    return weaponSlots;
}

OBJECT_CONVERTER_DEFINE(WeaponSlotData,
                        (uint8_t, id, UIntToJS<uint8_t>, JSToUInt<uint8_t>),
                        (uint32_t, ammo, UIntToJS<uint32_t>, JSToUInt<uint32_t>))

OBJECT_CONVERTER_DEFINE_TO_JS(PlayerKeyData,
                              (uint32_t, keys, UIntToJS<uint32_t>, JSToUInt<uint32_t>),
                              (int16_t, upDown, IntToJS<int16_t>, JSToInt<int16_t>),
                              (int16_t, leftRight, IntToJS<int16_t>, JSToInt<int16_t>))

OBJECT_CONVERTER_DEFINE_TO_JS(PlayerBulletData,
                              (Vector3, origin, VectorToJS<Vector3>, JSToVector<Vector3>),
                              (Vector3, hitPos, VectorToJS<Vector3>, JSToVector<Vector3>),
                              (Vector3, offset, VectorToJS<Vector3>, JSToVector<Vector3>),
                              (uint8_t, weapon, UIntToJS<uint8_t>, JSToUInt<uint8_t>),
                              (PlayerBulletHitType, hitType, EnumToJS, JSToEnum<PlayerBulletHitType>),
                              (uint16_t, hitID, UIntToJS<uint16_t>, JSToUInt<uint16_t>))

OBJECT_CONVERTER_DEFINE_TO_JS(PlayerSurfingData,
                              (PlayerSurfingData::Type, type, EnumToJS, JSToEnum<PlayerSurfingData::Type>),
                              (int, ID, IntToJS, JSToInt),
                              (Vector3, offset, VectorToJS<Vector3>, JSToVector<Vector3>))

OBJECT_CONVERTER_DEFINE_TO_JS(PlayerAimData,
                              (Vector3, camFrontVector, VectorToJS<Vector3>, JSToVector<Vector3>),
                              (Vector3, camPos, VectorToJS<Vector3>, JSToVector<Vector3>),
                              (float, aimZ, FloatToJS, JSToFloat),
                              (float, camZoom, FloatToJS, JSToFloat),
                              (float, aspectRatio, FloatToJS, JSToFloat),
                              (PlayerWeaponState, weaponState, EnumToJS, JSToEnum<PlayerWeaponState>),
                              (uint8_t, camMode, UIntToJS<uint8_t>, JSToUInt<uint8_t>))

OBJECT_CONVERTER_DEFINE_TO_JS(PlayerSpectateData,
                              (int, spectateID, IntToJS, JSToInt),
                              (PlayerSpectateData::ESpectateType, type, EnumToJS, JSToEnum<PlayerSpectateData::ESpectateType>))