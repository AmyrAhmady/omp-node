#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "Server/Components/Vehicles/vehicles.hpp"
#include "Server/Components/Actors/actors.hpp"

void WrapPlayer(IPlayer *player, v8::Local<v8::Context> context);