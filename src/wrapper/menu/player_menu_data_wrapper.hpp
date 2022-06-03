#pragma once
#include "Server/Components/Menus/menus.hpp"
#include "v8.h"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0xaa11838c542764e2, PlayerMenuDataHandleStorage)

WRAP_BASIC_DECLARE_WITH_CONSTRUCTOR(IPlayerMenuData)

std::vector<IExtension *> WrapPlayerMenuData(IPlayer *player,
                                             IPlayerMenuData *playerMenuData,
                                             v8::Local<v8::Context> context);
