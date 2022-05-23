#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "../logger.hpp"

BanEntry JSToBanEntry(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
v8::Local<v8::Object> BanEntryToJS(const BanEntry &entry, v8::Local<v8::Context>);