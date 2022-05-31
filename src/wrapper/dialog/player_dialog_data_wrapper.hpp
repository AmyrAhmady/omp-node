#pragma once
#include "Server/Components/Dialogs/dialogs.hpp"
#include "v8.h"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0x387d4b5d98147a04, PlayerDialogDataHandleStorage)

std::vector<IExtension *> WrapPlayerDialogData(IPlayer *player,
                                               IPlayerDialogData *playerDialogData,
                                               v8::Local<v8::Context> context);
