#pragma once
#include "sdk.hpp"
#include "Server/Components/Menus/menus.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapMenu(IMenu *menu, v8::Local<v8::Context> context);