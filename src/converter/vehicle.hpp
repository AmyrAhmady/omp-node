#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "../logger.hpp"
#include "Server/Components/Vehicles/vehicles.hpp"

IVehicle *JSToIVehicle(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
VehicleSpawnData JSToVehicleSpawnData(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
VehicleParams JSToVehicleParams(v8::Local<v8::Value> value, v8::Local<v8::Context> context);

v8::Local<v8::Value> IVehicleToJS(IVehicle &vehicle, v8::Local<v8::Context> context);
v8::Local<v8::Value> IVehicleToJS(IVehicle *vehicle, v8::Local<v8::Context> context);
v8::Local<v8::Array> CarriagesToJS(const StaticArray<IVehicle *, MAX_VEHICLE_CARRIAGES> &carriages,
                                   v8::Local<v8::Context> context);
v8::Local<v8::Object> VehicleSpawnDataToJS(const VehicleSpawnData &data, v8::Local<v8::Context> context);
v8::Local<v8::Object> VehicleParamsToJS(const VehicleParams &data, v8::Local<v8::Context> context);
v8::Local<v8::Array> VehicleColourToJS(const Pair<int, int> &vehicleColour, v8::Local<v8::Context> context);