#pragma once
#include "Server/Components/Classes/classes.hpp"
#include "v8.h"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0xf7750496835303c6, PlayerClassDataHandleStorage)

std::vector<IHandleStorage*> WrapPlayerClassData(IPlayer *player, IPlayerClassData *playerClassData, v8::Local<v8::Context> context);
