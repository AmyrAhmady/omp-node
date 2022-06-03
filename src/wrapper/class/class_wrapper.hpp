#pragma once
#include "sdk.hpp"
#include "Server/Components/Classes/classes.hpp"
#include "v8.h"
#include "../utils.hpp"

WRAP_BASIC_DECLARE_WITH_CONSTRUCTOR_INHERIT(IClass, IIDProvider)

void WrapClass(IClass *playerClass, v8::Local<v8::Context> context);
