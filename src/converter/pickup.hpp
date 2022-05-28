#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "../logger.hpp"
#include "Server/Components/Pickups/pickups.hpp"
#include "utils.hpp"

IPickup *JSToIPickup(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
IPickup &JSToIPickupRef(v8::Local<v8::Value> value, v8::Local<v8::Context> context);

v8::Local<v8::Value> IPickupToJS(IPickup &pickup, v8::Local<v8::Context> context);
v8::Local<v8::Value> IPickupToJS(IPickup *pickup, v8::Local<v8::Context> context);
