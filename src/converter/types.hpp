#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "../logger.hpp"
#include "utils.hpp"

typedef Pair<Hours, Minutes> HoursMinutes;
typedef Pair<bool, StringView> PairBoolStringView;

WorldTimePoint JSToWorldTimePoint(v8::Local<v8::Value> value,
                                  v8::Local<v8::Context> context,
                                  const WorldTimePoint &defaultValue);
Milliseconds JSToMilliseconds(v8::Local<v8::Value> value,
                              v8::Local<v8::Context> context,
                              const Milliseconds &defaultValue);
Seconds JSToSeconds(v8::Local<v8::Value> value, v8::Local<v8::Context> context, const Seconds &defaultValue);
Minutes JSToMinutes(v8::Local<v8::Value> value, v8::Local<v8::Context> context, const Minutes &defaultValue);
Hours JSToHours(v8::Local<v8::Value> value, v8::Local<v8::Context> context, const Hours &defaultValue);

template<typename VectorType>
VectorType JSToVector(v8::Local<v8::Value> value, v8::Local<v8::Context> context, const VectorType &defaultValue) {
    auto isolate = context->GetIsolate();
    if (value->IsUndefined()) {
        return defaultValue;
    }
    if (!value->IsArray()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An array is required").ToLocalChecked()));
        return {};
    }
    auto vectorLength = VectorType::length();
    if (value.As<v8::Array>()->Length() != vectorLength) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Array has wrong length").ToLocalChecked()));
        return {};
    }
    VectorType vector;
    for (typename VectorType::length_type i = 0; i < vectorLength; i++) {
        auto handle = value.As<v8::Array>()->Get(context, i);
        if (handle.IsEmpty() || handle.ToLocalChecked()->IsUndefined()) {
            isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                     "Vector coordinate is invalid").ToLocalChecked()));
            return {};
        }
        vector[i] = JSToFloat(handle.ToLocalChecked(), context);
    }
    return vector;
}

Colour JSToColour(v8::Local<v8::Value> value, v8::Local<v8::Context> context, const Colour &defaultValue);

WorldTimePoint JSToWorldTimePoint(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Milliseconds JSToMilliseconds(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Seconds JSToSeconds(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Minutes JSToMinutes(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Hours JSToHours(v8::Local<v8::Value> value, v8::Local<v8::Context> context);

template<typename VectorType>
VectorType JSToVector(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();
    if (!value->IsArray()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An array is required").ToLocalChecked()));
        return {};
    }
    auto vectorLength = VectorType::length();
    if (value.As<v8::Array>()->Length() != vectorLength) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Array has wrong length").ToLocalChecked()));
        return {};
    }
    VectorType vector;
    for (typename VectorType::length_type i = 0; i < vectorLength; i++) {
        auto handle = value.As<v8::Array>()->Get(context, i);
        if (handle.IsEmpty() || handle.ToLocalChecked()->IsUndefined()) {
            isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                     "Vector coordinate is invalid").ToLocalChecked()));
            return {};
        }
        vector[i] = JSToFloat(handle.ToLocalChecked(), context);
    }
    return vector;
}

GTAQuat JSToGTAQuat(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Colour JSToColour(v8::Local<v8::Value> value, v8::Local<v8::Context> context);

v8::Local<v8::Date> WorldTimePointToJS(const WorldTimePoint &point, v8::Local<v8::Context> context);
v8::Local<v8::Integer> TimePointToJS(const TimePoint &point, v8::Local<v8::Context> context);
v8::Local<v8::Integer> MillisecondsToJS(const Milliseconds &ms, v8::Local<v8::Context> context);
v8::Local<v8::Integer> SecondsToJS(const Seconds &s, v8::Local<v8::Context> context);
v8::Local<v8::Integer> MinutesToJS(const Minutes &m, v8::Local<v8::Context> context);
v8::Local<v8::Integer> HoursToJS(const Hours &h, v8::Local<v8::Context> context);
v8::Local<v8::Array> HoursMinutesToJS(const HoursMinutes &hoursMinutes, v8::Local<v8::Context> context);
v8::Local<v8::Array> PairBoolStringViewToJS(const PairBoolStringView &boolStringView, v8::Local<v8::Context> context);

template<typename VectorType>
v8::Local<v8::Array> VectorToJS(const VectorType &vector, v8::Local<v8::Context> context) {
    v8::EscapableHandleScope handle_scope(context->GetIsolate());
    auto vectorLength = VectorType::length();
    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), vectorLength);
    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();
    for (typename VectorType::length_type i = 0; i < vectorLength; i++) {
        array->Set(context, i, v8::Number::New(context->GetIsolate(), vector[i])).Check();
    }
    return handle_scope.Escape(array);
}

v8::Local<v8::Integer> ColourToJS(const Colour &colour, v8::Local<v8::Context> context);

OBJECT_CONVERTER_DECLARE_TO_JS(SemanticVersion)
