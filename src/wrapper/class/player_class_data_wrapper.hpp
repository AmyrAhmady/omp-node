#pragma once
#include "Server/Components/Classes/classes.hpp"
#include "v8.h"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0x64f5900e54bab59c, PlayerClassDataHandleStorage)

WRAP_BASIC_DECLARE_WITH_CONSTRUCTOR(IPlayerClassData)

std::vector<IExtension *> WrapPlayerClassData(IPlayer *player,
                                              IPlayerClassData *playerClassData,
                                              v8::Local<v8::Context> context);
