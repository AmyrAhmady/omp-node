#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"

typedef IEventDispatcher<PlayerEventHandler> IPlayerEventDispatcher;

v8::Local<v8::Value> WrapPlayerEventDispatcher(IPlayerEventDispatcher *dispatcher, v8::Local<v8::Context> context);
