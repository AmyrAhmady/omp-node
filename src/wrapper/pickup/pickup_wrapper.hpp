#pragma once
#include "sdk.hpp"
#include "Server/Components/Pickups/pickups.hpp"
#include "v8.h"
#include "../utils.hpp"

WRAP_BASIC_DECLARE_WITH_CONSTRUCTOR_INHERIT(IPickup, IEntity)

void WrapPickup(IPickup *vehicle, v8::Local<v8::Context> context);