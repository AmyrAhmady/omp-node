#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/Checkpoints/checkpoints.hpp"
#include "../utils.hpp"

typedef IEventDispatcher<PlayerCheckpointEventHandler> ICheckpointEventDispatcher;

EventDispatcherHandleStorage *WrapCheckpointEventDispatcher(ICheckpointEventDispatcher *dispatcher,
                                                            v8::Local<v8::Context> context) __attribute__((warn_unused_result));
