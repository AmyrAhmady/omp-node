#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapPlayerPool(IPlayerPool *playerPool, v8::Local<v8::Context> context);