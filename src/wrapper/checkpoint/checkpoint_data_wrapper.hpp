#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/Checkpoints/checkpoints.hpp"
#include "../utils.hpp"

v8::Local<v8::Value> WrapCheckpointData(ICheckpointData &data, v8::Local<v8::Context> context);
