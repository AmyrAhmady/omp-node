#pragma once
#include "Server/Components/Vehicles/vehicles.hpp"
#include "v8.h"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0xf7751496836403c6, PlayerVehicleDataHandleStorage)

std::vector<IHandleStorage*> WrapPlayerVehicleData(IPlayer *player, IPlayerVehicleData *playerVehicleData, v8::Local<v8::Context> context);
