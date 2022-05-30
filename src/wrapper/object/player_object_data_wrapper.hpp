#pragma once
#include "Server/Components/Objects/objects.hpp"
#include "v8.h"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0x6dfc820f4cb56665, PlayerObjectPoolEventDispatcherHandleStorage)
CREATE_HANDLE_STORAGE_EXTENSION(0x92606d05cbe6d1f0, PlayerObjectPoolHandleStorage)

std::vector<IHandleStorage*> WrapPlayerObjectData(IPlayer *player, IPlayerObjectData *objectPool, v8::Local<v8::Context> context);
