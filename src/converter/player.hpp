#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "../logger.hpp"
#include "utils.hpp"

typedef FlatPtrHashSet<IPlayer> FlatPtrHashSetIPlayer;
typedef StaticArray<uint16_t, NUM_SKILL_LEVELS> SkillLevels;

v8::Local<v8::Array> FlatPtrHashSetIPlayerToJS(const FlatPtrHashSetIPlayer &players, v8::Local<v8::Context> context);

v8::Local<v8::Array> WeaponSlotsToJS(const WeaponSlots &slots, v8::Local<v8::Context> context);
v8::Local<v8::Array> SkillLevelsToJS(const StaticArray<uint16_t, NUM_SKILL_LEVELS> &skillLevels,
                                     v8::Local<v8::Context> context);

WeaponSlots JSToWeaponSlots(v8::Local<v8::Value> slots, v8::Local<v8::Context> context);

OBJECT_CONVERTER_DECLARE(WeaponSlotData)

OBJECT_CONVERTER_DECLARE_TO_JS(PlayerKeyData)
OBJECT_CONVERTER_DECLARE_TO_JS(PlayerBulletData)
OBJECT_CONVERTER_DECLARE_TO_JS(PlayerSurfingData)
OBJECT_CONVERTER_DECLARE_TO_JS(PlayerAimData)
OBJECT_CONVERTER_DECLARE_TO_JS(PlayerSpectateData)