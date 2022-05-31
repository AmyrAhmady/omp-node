#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/Actors/actors.hpp"
#include "../utils.hpp"

typedef IEventDispatcher<ActorEventHandler> IActorEventDispatcher;

EventDispatcherHandleStorage *WrapActorEventDispatcher(IActorEventDispatcher *dispatcher,
                                                       v8::Local<v8::Context> context) __attribute__((warn_unused_result));
