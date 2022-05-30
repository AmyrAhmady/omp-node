#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/Classes/classes.hpp"
#include "../utils.hpp"

typedef IEventDispatcher<ClassEventHandler> IClassEventDispatcher;

EventDispatcherHandleStorage* WrapClassEventDispatcher(IClassEventDispatcher *dispatcher, v8::Local<v8::Context> context) __attribute__((warn_unused_result));
