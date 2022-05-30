#pragma once
#include "sdk.hpp"
#include "Server/Components/TextDraws/textdraws.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapPlayerTextDraw(IPlayerTextDraw *playerTextDraw, v8::Local<v8::Context> context);
