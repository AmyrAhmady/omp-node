#pragma once
#include "Server/Components/Objects/objects.hpp"
#include "v8.h"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0xdb224f4617686a0e, PlayerObjectPoolEventDispatcherHandleStorage)
CREATE_HANDLE_STORAGE_EXTENSION(0xc4b3bc14ecd0765d, PlayerObjectPoolHandleStorage)

std::vector<IExtension *> WrapPlayerObjectData(IPlayer *player,
                                               IPlayerObjectData *objectPool,
                                               v8::Local<v8::Context> context);
