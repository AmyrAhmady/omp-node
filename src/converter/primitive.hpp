#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"

float JSToFloat(v8::Local<v8::Value> value, v8::Local<v8::Context> context, float defaultValue);
int JSToInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context, int defaultValue);
int8_t JSToInt8T(v8::Local<v8::Value> value, v8::Local<v8::Context> context, int8_t defaultValue);
unsigned int JSToUInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context, int defaultValue);
Impl::String JSToString(v8::Local<v8::Value> value, v8::Local<v8::Context> context, Impl::String defaultValue);
bool JSToBool(v8::Local<v8::Value> value, v8::Local<v8::Context> context, bool defaultValue);

float JSToFloat(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
int JSToInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
int8_t JSToInt8T(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
unsigned int JSToUInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Impl::String JSToString(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
bool JSToBool(v8::Local<v8::Value> value, v8::Local<v8::Context> context);

v8::Local<v8::Number> FloatToJS(float value, v8::Local<v8::Context> context);
v8::Local<v8::Integer> IntToJS(int value, v8::Local<v8::Context> context);
v8::Local<v8::Integer> Int8TToJS(int8_t value, v8::Local<v8::Context> context);
v8::Local<v8::Integer> UIntToJS(unsigned int value, v8::Local<v8::Context> context);
v8::Local<v8::String> StringViewToJS(StringView str, v8::Local<v8::Context> context);
v8::Local<v8::Boolean> BoolToJS(bool value, v8::Local<v8::Context> context);