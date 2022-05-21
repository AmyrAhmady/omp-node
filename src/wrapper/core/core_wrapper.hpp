#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "config_wrapper.hpp"
#include "../../logger.hpp"
#include "../utils.hpp"

void WrapCore(ICore *core, v8::Local<v8::Context> context);