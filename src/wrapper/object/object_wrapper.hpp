#pragma once
#include "sdk.hpp"
#include "Server/Components/Objects/objects.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapObject(IObject *vehicle, v8::Local<v8::Context> context);
