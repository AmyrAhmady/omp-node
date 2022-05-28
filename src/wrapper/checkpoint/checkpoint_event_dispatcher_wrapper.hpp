#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/Checkpoints/checkpoints.hpp"
#include "../utils.hpp"

typedef IEventDispatcher<PlayerCheckpointEventHandler> ICheckpointEventDispatcher;

v8::Local<v8::Value> WrapCheckpointEventDispatcher(ICheckpointEventDispatcher *dispatcher, v8::Local<v8::Context> context);
