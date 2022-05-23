#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "../logger.hpp"
#include "Server/Components/Vehicles/vehicles.hpp"
#include "utils.hpp"

IVehicle *JSToIVehicle(v8::Local<v8::Value> value, v8::Local<v8::Context> context);

v8::Local<v8::Value> IVehicleToJS(IVehicle &vehicle, v8::Local<v8::Context> context);
v8::Local<v8::Value> IVehicleToJS(IVehicle *vehicle, v8::Local<v8::Context> context);
v8::Local<v8::Array> CarriagesToJS(const StaticArray<IVehicle *, MAX_VEHICLE_CARRIAGES> &carriages,
                                   v8::Local<v8::Context> context);
v8::Local<v8::Object> UnoccupiedVehicleUpdateToJS(const UnoccupiedVehicleUpdate &data, v8::Local<v8::Context> context);
v8::Local<v8::Array> VehicleColourToJS(const Pair<int, int> &vehicleColour, v8::Local<v8::Context> context);

OBJECT_CONVERTER_DECLARE(VehicleSpawnData)
OBJECT_CONVERTER_DECLARE(VehicleParams)
