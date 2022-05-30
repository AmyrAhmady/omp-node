#pragma once
#include "Server/Components/Checkpoints/checkpoints.hpp"
#include "v8.h"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0xc586f1de7d0920cd, PlayerCheckpointDataHandleStorage)
CREATE_HANDLE_STORAGE_EXTENSION(0xec271baf3dd77e77, PlayerCheckpointHandleStorage)
CREATE_HANDLE_STORAGE_EXTENSION(0x49182c34fbf4f0dd, PlayerRaceCheckpointHandleStorage)

std::vector<IHandleStorage*> WrapPlayerCheckpointData(IPlayer *player, IPlayerCheckpointData *playerCheckpointData, v8::Local<v8::Context> context);
