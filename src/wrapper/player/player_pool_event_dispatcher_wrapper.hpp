#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"

typedef PoolEventHandler<IPlayer> PlayerPoolEventHandler;
typedef IEventDispatcher<PoolEventHandler<IPlayer>> IPlayerPoolEventDispatcher;

v8::Local<v8::Value> WrapPlayerPoolEventDispatcher(IPlayerPoolEventDispatcher *dispatcher,
                                                   v8::Local<v8::Context> context);
