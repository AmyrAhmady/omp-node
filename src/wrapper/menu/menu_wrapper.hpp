#pragma once
#include "sdk.hpp"
#include "Server/Components/Menus/menus.hpp"
#include "v8.h"
#include "../utils.hpp"

WRAP_BASIC_DECLARE_WITH_CONSTRUCTOR_INHERIT(IMenu, IIDProvider)

void WrapMenu(IMenu *menu, v8::Local<v8::Context> context);
