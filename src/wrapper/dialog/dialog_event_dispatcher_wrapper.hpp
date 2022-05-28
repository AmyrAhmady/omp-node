#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/Dialogs/dialogs.hpp"
#include "../utils.hpp"

typedef IEventDispatcher<PlayerDialogEventHandler> IDialogEventDispatcher;

v8::Local<v8::Value> WrapDialogEventDispatcher(IDialogEventDispatcher *dispatcher, v8::Local<v8::Context> context);
