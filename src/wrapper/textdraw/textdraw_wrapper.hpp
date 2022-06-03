#pragma once
#include "sdk.hpp"
#include "Server/Components/TextDraws/textdraws.hpp"
#include "v8.h"
#include "../utils.hpp"

WRAP_BASIC_DECLARE_WITH_CONSTRUCTOR_INHERIT(ITextDraw, ITextDrawBase)

void WrapTextDraw(ITextDraw *textDraw, v8::Local<v8::Context> context);
