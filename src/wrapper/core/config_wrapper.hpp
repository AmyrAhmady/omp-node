#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapConfig(IConfig *config, v8::Local<v8::Context> context);