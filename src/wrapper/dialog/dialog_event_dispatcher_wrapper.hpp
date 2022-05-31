#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/Dialogs/dialogs.hpp"
#include "../utils.hpp"

typedef IEventDispatcher<PlayerDialogEventHandler> IDialogEventDispatcher;

EventDispatcherHandleStorage *WrapDialogEventDispatcher(IDialogEventDispatcher *dispatcher,
                                                        v8::Local<v8::Context> context) __attribute__((warn_unused_result));
