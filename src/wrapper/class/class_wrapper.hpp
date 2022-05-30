#pragma once
#include "sdk.hpp"
#include "Server/Components/Classes/classes.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapClass(IClass *playerClass, v8::Local<v8::Context> context);
