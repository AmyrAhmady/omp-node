#include "player.hpp"
#include "primitive.hpp"
#include "types.hpp"
#include "../wrapper/utils.hpp"

IPlayer *JSToIPlayer(v8::Local<v8::Value> value, v8::Local<v8::Context> context, IPlayer *defaultValue) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(value.As<v8::Object>()->GetInternalField(0));

    return static_cast<IPlayer *>( pointer->Value());
}

IPlayer *JSToIPlayer(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(value.As<v8::Object>()->GetInternalField(0));

    return static_cast<IPlayer *>( pointer->Value());
}

IPlayer &JSToIPlayerRef(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(value.As<v8::Object>()->GetInternalField(0));

    auto *playerPointerValue = static_cast<IPlayer *>(pointer->Value());

    return *playerPointerValue;
}

v8::Local<v8::Value> IPlayerToJS(IPlayer &player, v8::Local<v8::Context> context) {
    auto ext = GetHandleStorageExtension(&player);

    return ext->get();
}
v8::Local<v8::Value> IPlayerToJS(IPlayer *player, v8::Local<v8::Context> context) {
    if (player == nullptr) {
        return v8::Null(context->GetIsolate());
    }

    auto ext = GetHandleStorageExtension(player);

    return ext->get();
}

v8::Local<v8::Array> FlatPtrHashSetIPlayerToJS(const FlatPtrHashSet<IPlayer> &players, v8::Local<v8::Context> context) {
    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), players.size());

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    int i = 0;
    for (auto player: players) {
        array->Set(context, i++, IPlayerToJS(*player, context)).Check();
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