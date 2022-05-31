#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "../logger.hpp"
#include "utils.hpp"
#include "Server/Components/GangZones/gangzones.hpp"

typedef FlatPtrHashSet<IGangZone> FlatPtrHashSetIGangZone;

OBJECT_CONVERTER_DECLARE(GangZonePos)

v8::Local<v8::Array> FlatPtrHashSetIGangZoneToJS(const FlatPtrHashSetIGangZone &gangZones,
                                                 v8::Local<v8::Context> context);
