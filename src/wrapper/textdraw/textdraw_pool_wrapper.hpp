#pragma once
#include "Server/Components/TextDraws/textdraws.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapTextDrawPool(ITextDrawsComponent *textDrawPool, v8::Local<v8::Context> context);