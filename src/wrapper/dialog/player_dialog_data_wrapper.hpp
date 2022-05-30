#pragma once
#include "Server/Components/Dialogs/dialogs.hpp"
#include "v8.h"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0xf77514a6835303c6, PlayerDialogDataHandleStorage)

std::vector<IHandleStorage*> WrapPlayerDialogData(IPlayer *player, IPlayerDialogData *playerDialogData, v8::Local<v8::Context> context);
