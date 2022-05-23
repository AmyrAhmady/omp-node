#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "../logger.hpp"

IPlayer *JSToIPlayer(v8::Local<v8::Value> value, v8::Local<v8::Context> context, IPlayer *defaultValue);
IPlayer *JSToIPlayer(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
WeaponSlotData JSToWeaponSlotData(v8::Local<v8::Value>, v8::Local<v8::Context> context);

v8::Local<v8::Value> IPlayerToJS(IPlayer &player, v8::Local<v8::Context> context);
v8::Local<v8::Value> IPlayerToJS(IPlayer *player, v8::Local<v8::Context> context);
v8::Local<v8::Array> FlatPtrHashSetIPlayerToJS(const FlatPtrHashSet<IPlayer> &players, v8::Local<v8::Context> context);
v8::Local<v8::Object> PlayerKeyDataToJS(PlayerKeyData &data, v8::Local<v8::Context>);
v8::Local<v8::Object> PlayerBulletDataToJS(const PlayerBulletData &bulletData, v8::Local<v8::Context>);
v8::Local<v8::Object> WeaponSlotDataToJS(const WeaponSlotData &slotData, v8::Local<v8::Context>);

v8::Local<v8::Array> WeaponSlotsToJS(const WeaponSlots &slots, v8::Local<v8::Context> context);
v8::Local<v8::Array> SkillLevelsToJS(const StaticArray<uint16_t, NUM_SKILL_LEVELS> &skillLevels,
                                     v8::Local<v8::Context> context);

v8::Local<v8::Object> PlayerSurfingDataToJS(const PlayerSurfingData &data, v8::Local<v8::Context> context);
v8::Local<v8::Object> PlayerAimDataToJS(const PlayerAimData &data, v8::Local<v8::Context> context);
v8::Local<v8::Object> PlayerSpectateDataToJS(const PlayerSpectateData &data, v8::Local<v8::Context> context);

