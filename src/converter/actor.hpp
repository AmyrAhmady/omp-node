#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "../logger.hpp"
#include "utils.hpp"
#include "Server/Components/Actors/actors.hpp"

OBJECT_CONVERTER_DECLARE(ActorSpawnData)

IActor *JSToIActor(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
IActor &JSToIActorRef(v8::Local<v8::Value> value, v8::Local<v8::Context> context);

v8::Local<v8::Value> IActorToJS(IActor &actor, v8::Local<v8::Context> context);
v8::Local<v8::Value> IActorToJS(IActor *actor, v8::Local<v8::Context> context);
