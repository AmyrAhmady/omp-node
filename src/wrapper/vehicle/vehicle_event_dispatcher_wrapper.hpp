#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/Vehicles/vehicles.hpp"
#include "../utils.hpp"

typedef IEventDispatcher<VehicleEventHandler> IVehicleEventDispatcher;

EventDispatcherHandleStorage *WrapVehicleEventDispatcher(IVehicleEventDispatcher *dispatcher,
                                                         v8::Local<v8::Context> context) __attribute__((warn_unused_result));
