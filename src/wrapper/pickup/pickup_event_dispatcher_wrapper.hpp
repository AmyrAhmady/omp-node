#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/Pickups/pickups.hpp"
#include "../utils.hpp"

typedef IEventDispatcher<PickupEventHandler> IPickupEventDispatcher;

v8::Local<v8::Value> WrapPickupEventDispatcher(IPickupEventDispatcher *dispatcher, v8::Local<v8::Context> context);
