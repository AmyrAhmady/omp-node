#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "../logger.hpp"
#include "utils.hpp"
#include "Server/Components/GangZones/gangzones.hpp"

typedef FlatPtrHashSet<IGangZone> FlatPtrHashSetIGangZone;

OBJECT_CONVERTER_DECLARE(GangZonePos)

IGangZone *JSToIGangZone(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
IGangZone &JSToIGangZoneRef(v8::Local<v8::Value> value, v8::Local<v8::Context> context);

v8::Local<v8::Value> IGangZoneToJS(IGangZone &gangZone, v8::Local<v8::Context> context);
v8::Local<v8::Value> IGangZoneToJS(IGangZone *gangZone, v8::Local<v8::Context> context);

v8::Local<v8::Array> FlatPtrHashSetIGangZoneToJS(const FlatPtrHashSetIGangZone &gangZones, v8::Local<v8::Context> context);