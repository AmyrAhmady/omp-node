#pragma once
#include "sdk.hpp"
#include "Server/Components/Actors/actors.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapActor(IActor *actor, v8::Local<v8::Context> context);