#pragma once
#include "Server/Components/TextLabels/textlabels.hpp"
#include "v8.h"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0x6daa2a555660389f, PlayerTextLabelPoolEventDispatcherHandleStorage)
CREATE_HANDLE_STORAGE_EXTENSION(0x97d0fd5b0c807ad2, PlayerTextLabelPoolHandleStorage)

WRAP_BASIC_DECLARE_WITH_CONSTRUCTOR(IPlayerTextLabelData)

std::vector<IExtension *> WrapPlayerTextLabelData(IPlayer *player,
                                                  IPlayerTextLabelData *textLabelPool,
                                                  v8::Local<v8::Context> context);
