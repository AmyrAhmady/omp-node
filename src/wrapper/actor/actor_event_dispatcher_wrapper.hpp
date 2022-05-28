#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/Actors/actors.hpp"
#include "../utils.hpp"

typedef IEventDispatcher<ActorEventHandler> IActorEventDispatcher;

v8::Local<v8::Value> WrapActorEventDispatcher(IActorEventDispatcher *dispatcher, v8::Local<v8::Context> context);
