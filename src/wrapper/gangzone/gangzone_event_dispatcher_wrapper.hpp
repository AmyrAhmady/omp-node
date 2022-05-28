#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/GangZones/gangzones.hpp"
#include "../utils.hpp"

typedef IEventDispatcher<GangZoneEventHandler> IGangZoneEventDispatcher;

v8::Local<v8::Value> WrapGangZoneEventDispatcher(IGangZoneEventDispatcher *dispatcher, v8::Local<v8::Context> context);
