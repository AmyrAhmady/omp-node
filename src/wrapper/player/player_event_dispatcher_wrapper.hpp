#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"

typedef IEventDispatcher<PlayerEventHandler> IPlayerEventDispatcher;

EventDispatcherHandleStorage* WrapPlayerEventDispatcher(IPlayerEventDispatcher *dispatcher, v8::Local<v8::Context> context) __attribute__((warn_unused_result));
