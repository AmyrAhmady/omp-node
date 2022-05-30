#pragma once
#include "Server/Components/Checkpoints/checkpoints.hpp"
#include "v8.h"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0xf7750496835303c5, PlayerCheckpointDataHandleStorage)
CREATE_HANDLE_STORAGE_EXTENSION(0xc1a6b86b95e5ca63, PlayerCheckpointHandleStorage)
CREATE_HANDLE_STORAGE_EXTENSION(0xb2ccc83d81558211, PlayerRaceCheckpointHandleStorage)

std::vector<IHandleStorage*> WrapPlayerCheckpointData(IPlayer *player, IPlayerCheckpointData *playerCheckpointData, v8::Local<v8::Context> context);
