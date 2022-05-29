#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"

typedef IEventDispatcher<PlayerUpdateEventHandler> IPlayerUpdateEventDispatcher;

CREATE_HANDLE_STORAGE_EXTENSION(0x052eb73e418e2129, PlayerUpdateEventDispatcherHandleStorage)

PlayerUpdateEventDispatcherHandleStorage* WrapPlayerUpdateEventDispatcher(IPlayerUpdateEventDispatcher *dispatcher,
                                                     v8::Local<v8::Context> context) __attribute__((warn_unused_result));
