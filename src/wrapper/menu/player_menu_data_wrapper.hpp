#pragma once
#include "Server/Components/Menus/menus.hpp"
#include "v8.h"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0xaa11838c542764e2, PlayerMenuDataHandleStorage)

std::vector<IHandleStorage*> WrapPlayerMenuData(IPlayer *player, IPlayerMenuData *playerMenuData, v8::Local<v8::Context> context);
