#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "../logger.hpp"

WorldTimePoint JSToWorldTimePoint(v8::Local<v8::Value> value,
                                  v8::Local<v8::Context> context,
                                  const WorldTimePoint &defaultValue);
Milliseconds JSToMilliseconds(v8::Local<v8::Value> value,
                              v8::Local<v8::Context> context,
                              const Milliseconds &defaultValue);
Seconds JSToSeconds(v8::Local<v8::Value> value,
                              v8::Local<v8::Context> context,
                              const Seconds &defaultValue);
Minutes JSToMinutes(v8::Local<v8::Value> value,
                              v8::Local<v8::Context> context,
                              const Minutes &defaultValue);
Hours JSToHours(v8::Local<v8::Value> value,
                              v8::Local<v8::Context> context,
                              const Hours &defaultValue);
Vector2 JSToVector2(v8::Local<v8::Value> value, v8::Local<v8::Context> context, const Vector2 &defaultValue);
Vector3 JSToVector3(v8::Local<v8::Value> value, v8::Local<v8::Context> context, const Vector3 &defaultValue);
Vector4 JSToVector4(v8::Local<v8::Value> value, v8::Local<v8::Context> context, const Vector4 &defaultValue);
Colour JSToColour(v8::Local<v8::Value> value, v8::Local<v8::Context> context, const Colour &defaultValue);

WorldTimePoint JSToWorldTimePoint(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Milliseconds JSToMilliseconds(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Seconds JSToSeconds(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Minutes JSToMinutes(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Hours JSToHours(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Vector2 JSToVector2(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Vector3 JSToVector3(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Vector4 JSToVector4(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
GTAQuat JSToGTAQuat(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Colour JSToColour(v8::Local<v8::Value> value, v8::Local<v8::Context> context);

v8::Local<v8::Date> WorldTimePointToJS(const WorldTimePoint &point, v8::Local<v8::Context> context);
v8::Local<v8::Date> TimePointToJS(const TimePoint &point, v8::Local<v8::Context> context);
v8::Local<v8::Integer> MillisecondsToJS(const Milliseconds &ms, v8::Local<v8::Context> context);
v8::Local<v8::Integer> SecondsToJS(const Seconds &s, v8::Local<v8::Context> context);
v8::Local<v8::Integer> MinutesToJS(const Minutes &m, v8::Local<v8::Context> context);
v8::Local<v8::Integer> HoursToJS(const Hours &h, v8::Local<v8::Context> context);
v8::Local<v8::Array> HoursMinutesToJS(const Pair<Hours, Minutes> &hoursMinutes, v8::Local<v8::Context> context);
v8::Local<v8::Array> Vector2ToJS(const Vector2 &vector, v8::Local<v8::Context> context);
v8::Local<v8::Array> Vector3ToJS(const Vector3 &vector, v8::Local<v8::Context> context);
v8::Local<v8::Array> Vector4ToJS(const Vector4 &vector, v8::Local<v8::Context> context);
v8::Local<v8::Integer> ColourToJS(const Colour &colour, v8::Local<v8::Context> context);

v8::Local<v8::Object> SemanticVersionToJS(SemanticVersion &version, v8::Local<v8::Context>);