#pragma once
#include "Server/Components/Variables/variables.hpp"
#include "v8.h"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0xe76bbd9069e21c25, PlayerVariableDataHandleStorage)

std::vector<IHandleStorage*> WrapPlayerVariableData(IPlayer *player, IPlayerVariableData *playerVariableData, v8::Local<v8::Context> context);
