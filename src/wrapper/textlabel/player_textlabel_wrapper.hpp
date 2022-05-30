#pragma once
#include "sdk.hpp"
#include "Server/Components/TextLabels/textlabels.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapPlayerTextLabel(IPlayerTextLabel *playerTextLabel, v8::Local<v8::Context> context);
