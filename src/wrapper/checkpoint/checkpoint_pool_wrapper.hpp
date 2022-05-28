#pragma once
#include "Server/Components/Checkpoints/checkpoints.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapCheckpointPool(ICheckpointsComponent *checkpointPool, v8::Local<v8::Context> context);