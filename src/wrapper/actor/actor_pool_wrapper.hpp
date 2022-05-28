#pragma once
#include "Server/Components/Actors/actors.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapActorPool(IActorsComponent *actorPool, v8::Local<v8::Context> context);