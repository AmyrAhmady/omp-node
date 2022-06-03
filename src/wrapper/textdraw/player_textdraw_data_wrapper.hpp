#pragma once
#include "Server/Components/TextDraws/textdraws.hpp"
#include "v8.h"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0x6faaf9a1a91e1f94, PlayerTextDrawPoolEventDispatcherHandleStorage)
CREATE_HANDLE_STORAGE_EXTENSION(0xe5ea5a58bb0bf05a, PlayerTextDrawPoolHandleStorage)

WRAP_BASIC_DECLARE_WITH_CONSTRUCTOR(IPlayerTextDrawData)

std::vector<IExtension *> WrapPlayerTextDrawData(IPlayer *player,
                                                 IPlayerTextDrawData *textDrawPool,
                                                 v8::Local<v8::Context> context);
