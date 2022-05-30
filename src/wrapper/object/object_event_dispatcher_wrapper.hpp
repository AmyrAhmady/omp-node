#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/Objects/objects.hpp"
#include "../utils.hpp"

typedef IEventDispatcher<ObjectEventHandler> IObjectEventDispatcher;

EventDispatcherHandleStorage* WrapObjectEventDispatcher(IObjectEventDispatcher *dispatcher, v8::Local<v8::Context> context) __attribute__((warn_unused_result));
