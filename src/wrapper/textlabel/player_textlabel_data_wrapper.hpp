#pragma once
#include "Server/Components/TextLabels/textlabels.hpp"
#include "v8.h"
#include "../utils.hpp"


CREATE_HANDLE_STORAGE_EXTENSION(0x6dc30e7c5bd119b4, PlayerTextLabelPoolEventDispatcherHandleStorage)
CREATE_HANDLE_STORAGE_EXTENSION(0xeb2e71a88e86d556, PlayerTextLabelPoolHandleStorage)

std::vector<IHandleStorage*> WrapPlayerTextLabelData(IPlayer *player, IPlayerTextLabelData *textLabelPool, v8::Local<v8::Context> context);
