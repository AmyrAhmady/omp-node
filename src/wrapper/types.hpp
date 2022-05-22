#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "../logger.hpp"

WorldTimePoint JSToWorldTimePoint(v8::Local<v8::Value> value,
                                  v8::Local<v8::Context> context,
                                  WorldTimePoint defaultValue);
Vector2 JSToVector2(v8::Local<v8::Value> value, v8::Local<v8::Context> context, Vector2 defaultValue);
Vector3 JSToVector3(v8::Local<v8::Value> value, v8::Local<v8::Context> context, Vector3 defaultValue);
Vector4 JSToVector4(v8::Local<v8::Value> value, v8::Local<v8::Context> context, Vector4 defaultValue);

WorldTimePoint JSToWorldTimePoint(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Vector2 JSToVector2(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Vector3 JSToVector3(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Vector4 JSToVector4(v8::Local<v8::Value> value, v8::Local<v8::Context> context);

v8::Local<v8::Date> WorldTimePointToJS(WorldTimePoint point, v8::Local<v8::Context> context);
v8::Local<v8::Array> Vector2ToJS(Vector2 vector, v8::Local<v8::Context> context);
v8::Local<v8::Array> Vector3ToJS(Vector3 vector, v8::Local<v8::Context> context);
v8::Local<v8::Array> Vector4ToJS(Vector4 vector, v8::Local<v8::Context> context);

v8::Local<v8::Object> SemanticVersionToJS(SemanticVersion &version, v8::Local<v8::Context>);