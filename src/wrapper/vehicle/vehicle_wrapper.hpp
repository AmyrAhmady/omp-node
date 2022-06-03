#pragma once
#include "sdk.hpp"
#include "Server/Components/Vehicles/vehicles.hpp"
#include "v8.h"
#include "../utils.hpp"

WRAP_BASIC_DECLARE_WITH_CONSTRUCTOR_INHERIT(IVehicle, IEntity)

void WrapVehicle(IVehicle *vehicle, v8::Local<v8::Context> context);