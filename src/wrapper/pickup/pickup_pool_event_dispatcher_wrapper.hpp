#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "Server/Components/Pickups/pickups.hpp"

typedef PoolEventHandler<IPickup> PickupPoolEventHandler;
typedef IEventDispatcher<PoolEventHandler<IPickup>> IPickupPoolEventDispatcher;

v8::Local<v8::Value> WrapPickupPoolEventDispatcher(IPickupPoolEventDispatcher *dispatcher,
                                                   v8::Local<v8::Context> context);
