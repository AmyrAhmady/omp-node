#pragma once
#include "Server/Components/Menus/menus.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapMenuPool(IMenusComponent *menuPool, v8::Local<v8::Context> context);