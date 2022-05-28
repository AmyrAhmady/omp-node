#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "../logger.hpp"
#include "Server/Components/Vehicles/vehicles.hpp"
#include "utils.hpp"

typedef StaticArray<uint8_t, MAX_VEHICLE_MODELS> VehicleModels;
typedef Pair<int, int> VehicleColour;
typedef StaticArray<IVehicle *, MAX_VEHICLE_CARRIAGES> VehicleCarriages;

v8::Local<v8::Array> VehicleCarriagesToJS(const VehicleCarriages &carriages, v8::Local<v8::Context> context);
v8::Local<v8::Array> VehicleModelsToJS(const VehicleModels &models, v8::Local<v8::Context> context);
v8::Local<v8::Array> VehicleColourToJS(const Pair<int, int> &vehicleColour, v8::Local<v8::Context> context);

OBJECT_CONVERTER_DECLARE(VehicleSpawnData)
OBJECT_CONVERTER_DECLARE(VehicleParams)
OBJECT_CONVERTER_DECLARE(UnoccupiedVehicleUpdate)
