#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapPlayerEventDispatcher(HandleStorage &storage,
                               IEventDispatcher<PlayerEventHandler> *dispatcher,
                               v8::Local<v8::Context> context);