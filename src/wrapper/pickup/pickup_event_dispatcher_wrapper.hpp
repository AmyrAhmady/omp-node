#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/Pickups/pickups.hpp"
#include "../utils.hpp"

typedef IEventDispatcher<PickupEventHandler> IPickupEventDispatcher;

EventDispatcherHandleStorage *WrapPickupEventDispatcher(IPickupEventDispatcher *dispatcher,
                                                        v8::Local<v8::Context> context) __attribute__((warn_unused_result));
