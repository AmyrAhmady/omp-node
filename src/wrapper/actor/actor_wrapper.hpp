#pragma once
#include "sdk.hpp"
#include "Server/Components/Actors/actors.hpp"
#include "v8.h"
#include "../utils.hpp"

WRAP_BASIC_DECLARE_WITH_CONSTRUCTOR_INHERIT(IActor, IEntity)

void WrapActor(IActor *actor, v8::Local<v8::Context> context);