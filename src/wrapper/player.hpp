#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "../logger.hpp"

IPlayer *JSToIPlayer(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
WeaponSlotData JSToWeaponSlotData(v8::Local<v8::Value>, v8::Local<v8::Context> context);

v8::Local<v8::Object> PlayerKeyDataToJS(PlayerKeyData &data, v8::Local<v8::Context>);
v8::Local<v8::Object> PlayerBulletDataToJS(const PlayerBulletData &bulletData, v8::Local<v8::Context>);
v8::Local<v8::Object> WeaponSlotDataToJS(const WeaponSlotData &slotData, v8::Local<v8::Context>);


v8::Local<v8::Array> WeaponSlotsToJS(WeaponSlots slots, v8::Local<v8::Context> context);