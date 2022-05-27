#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"

typedef IEventDispatcher<PlayerUpdateEventHandler> IPlayerUpdateEventDispatcher;

v8::Local<v8::Value> WrapPlayerUpdateEventDispatcher(IPlayerUpdateEventDispatcher *dispatcher,
                                                     v8::Local<v8::Context> context);
