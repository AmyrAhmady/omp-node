#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/TextDraws/textdraws.hpp"
#include "../utils.hpp"

typedef IEventDispatcher<TextDrawEventHandler> ITextDrawEventDispatcher;

EventDispatcherHandleStorage *WrapTextDrawEventDispatcher(ITextDrawEventDispatcher *dispatcher,
                                                          v8::Local<v8::Context> context) __attribute__((warn_unused_result));
