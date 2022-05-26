#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"

typedef PoolEventHandler<IVehicle> VehiclePoolEventHandler;
typedef IEventDispatcher<PoolEventHandler<IVehicle>> IVehiclePoolEventDispatcher;

v8::Local<v8::Value> WrapVehiclePoolEventDispatcher(IVehiclePoolEventDispatcher *dispatcher,
                                                   v8::Local<v8::Context> context);
