#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/GangZones/gangzones.hpp"
#include "../utils.hpp"

typedef IEventDispatcher<GangZoneEventHandler> IGangZoneEventDispatcher;

EventDispatcherHandleStorage* WrapGangZoneEventDispatcher(IGangZoneEventDispatcher *dispatcher, v8::Local<v8::Context> context) __attribute__((warn_unused_result));
