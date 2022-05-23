#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/Vehicles/vehicles.hpp"
#include "../utils.hpp"

typedef IEventDispatcher<VehicleEventHandler> IVehicleEventDispatcher;

v8::Local<v8::Value> WrapVehicleEventDispatcher(IVehicleEventDispatcher *dispatcher, v8::Local<v8::Context> context);
