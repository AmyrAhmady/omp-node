#pragma once
#include "Server/Components/Vehicles/vehicles.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapVehiclePool(IVehiclesComponent *vehiclePool, v8::Local<v8::Context> context);