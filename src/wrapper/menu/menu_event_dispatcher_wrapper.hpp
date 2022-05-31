#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/Menus/menus.hpp"
#include "../utils.hpp"

typedef IEventDispatcher<MenuEventHandler> IMenuEventDispatcher;

EventDispatcherHandleStorage *WrapMenuEventDispatcher(IMenuEventDispatcher *dispatcher,
                                                      v8::Local<v8::Context> context) __attribute__((warn_unused_result));
