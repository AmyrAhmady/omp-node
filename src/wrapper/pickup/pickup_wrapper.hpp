#pragma once
#include "sdk.hpp"
#include "Server/Components/Pickups/pickups.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapPickup(IPickup *vehicle, v8::Local<v8::Context> context);