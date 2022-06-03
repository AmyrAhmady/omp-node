#pragma once
#include "sdk.hpp"
#include "Server/Components/Objects/objects.hpp"
#include "v8.h"
#include "../utils.hpp"

WRAP_BASIC_DECLARE_WITH_CONSTRUCTOR_INHERIT(IPlayerObject, IBaseObject)

void WrapPlayerObject(IPlayerObject *playerObject, v8::Local<v8::Context> context);
