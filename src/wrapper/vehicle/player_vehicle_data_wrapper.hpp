#pragma once
#include "Server/Components/Vehicles/vehicles.hpp"
#include "v8.h"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0xf30ea3ef828d3e09, PlayerVehicleDataHandleStorage)

std::vector<IExtension *> WrapPlayerVehicleData(IPlayer *player,
                                                IPlayerVehicleData *playerVehicleData,
                                                v8::Local<v8::Context> context);
