#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "Server/Components/Vehicles/vehicles.hpp"
#include "Server/Components/Actors/actors.hpp"

WRAP_BASIC_DECLARE_WITH_CONSTRUCTOR_INHERIT(IPlayer, IEntity)

void WrapPlayer(IPlayer *player, v8::Local<v8::Context> context);