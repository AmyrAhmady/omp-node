#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"

v8::Local<v8::Value> WrapPlayerEventDispatcher(IEventDispatcher<PlayerEventHandler> *dispatcher,
                                               v8::Local<v8::Context> context);