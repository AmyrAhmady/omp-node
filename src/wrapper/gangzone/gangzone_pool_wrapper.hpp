#pragma once
#include "Server/Components/GangZones/gangzones.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapGangZonePool(IGangZonesComponent *gangZonePool, v8::Local<v8::Context> context);