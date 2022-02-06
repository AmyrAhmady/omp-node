#pragma once
#include "sdk.hpp"
#include "Server/Components/Vehicles/vehicles.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapVehicle(HandleStorage &storage, IVehicle *vehicle, v8::Local<v8::Context> context);