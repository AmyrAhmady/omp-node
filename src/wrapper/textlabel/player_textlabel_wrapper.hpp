#pragma once
#include "sdk.hpp"
#include "Server/Components/TextLabels/textlabels.hpp"
#include "v8.h"
#include "../utils.hpp"

WRAP_BASIC_DECLARE_WITH_CONSTRUCTOR_INHERIT(IPlayerTextLabel, ITextLabelBase)

void WrapPlayerTextLabel(IPlayerTextLabel *playerTextLabel, v8::Local<v8::Context> context);
