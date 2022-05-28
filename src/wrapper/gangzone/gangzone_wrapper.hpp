#pragma once
#include "sdk.hpp"
#include "Server/Components/GangZones/gangzones.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapGangZone(IGangZone *gangZone, v8::Local<v8::Context> context);