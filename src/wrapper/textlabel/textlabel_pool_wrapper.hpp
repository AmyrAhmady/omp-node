#pragma once
#include "Server/Components/TextLabels/textlabels.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapTextLabelPool(ITextLabelsComponent *textLabelPool, v8::Local<v8::Context> context);
