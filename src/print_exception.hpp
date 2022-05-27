#pragma once
#define NODE_WANT_INTERNALS 1
#include "node.h"
#include "env.h"
#include "env-inl.h"
#include "util.h"
#include "v8.h"

void PrintException(v8::Isolate *isolate,
                    v8::Local<v8::Context> context,
                    v8::Local<v8::Value> err,
                    v8::Local<v8::Message> message);