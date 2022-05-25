#pragma once
#include "Server/Components/Pickups/pickups.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapPickupPool(IPickupsComponent *pickupPool, v8::Local<v8::Context> context);