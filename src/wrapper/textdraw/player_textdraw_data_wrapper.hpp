#pragma once
#include "Server/Components/TextDraws/textdraws.hpp"
#include "v8.h"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0x7f595d158415bb64, PlayerTextDrawPoolEventDispatcherHandleStorage)
CREATE_HANDLE_STORAGE_EXTENSION(0x73613a71d86358a9, PlayerTextDrawPoolHandleStorage)

std::vector<IHandleStorage*> WrapPlayerTextDrawData(IPlayer *player, IPlayerTextDrawData *textDrawPool, v8::Local<v8::Context> context);