#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"

float JSToFloat(v8::Local<v8::Value> value, v8::Local<v8::Context> context, float defaultValue);
Impl::String JSToString(v8::Local<v8::Value> value, v8::Local<v8::Context> context, Impl::String defaultValue);
bool JSToBool(v8::Local<v8::Value> value, v8::Local<v8::Context> context, bool defaultValue);

float JSToFloat(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
Impl::String JSToString(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
bool JSToBool(v8::Local<v8::Value> value, v8::Local<v8::Context> context);

v8::Local<v8::Number> FloatToJS(float value, v8::Local<v8::Context> context);
v8::Local<v8::String> StringViewToJS(StringView str, v8::Local<v8::Context> context);
v8::Local<v8::Boolean> BoolToJS(bool value, v8::Local<v8::Context> context);

template <typename Enum>
Enum JSToEnum(v8::Local<v8::Value> value, v8::Local<v8::Context> context, Enum defaultValue) {
    if (value->IsUndefined()) {
        return defaultValue;
    }

    using enumUndelyingType = typename std::underlying_type<Enum>::type;

    if (std::is_unsigned<enumUndelyingType>::value) {
        return static_cast<Enum>(static_cast<enumUndelyingType>(value->ToInteger(context).ToLocalChecked()->Uint32Value(context).ToChecked()));
    } else {
        return static_cast<Enum>(static_cast<enumUndelyingType>(value->ToInteger(context).ToLocalChecked()->Int32Value(context).ToChecked()));
    }
}

template <typename Enum>
Enum JSToEnum(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return {};
    }

    using enumUndelyingType = typename std::underlying_type<Enum>::type;

    if (std::is_unsigned<enumUndelyingType>::value) {
        return static_cast<Enum>(static_cast<enumUndelyingType>(value->ToInteger(context).ToLocalChecked()->Uint32Value(context).ToChecked()));
    } else {
        return static_cast<Enum>(static_cast<enumUndelyingType>(value->ToInteger(context).ToLocalChecked()->Int32Value(context).ToChecked()));
    }
}

template<typename Enum>
v8::Local<v8::Integer> EnumToJS(Enum value, v8::Local<v8::Context> context) {
    using enumUndelyingType = typename std::underlying_type<Enum>::type;

    if (std::is_unsigned<enumUndelyingType>::value) {
        return v8::Integer::NewFromUnsigned(context->GetIsolate(), static_cast<enumUndelyingType>(value));
    } else {
        return v8::Integer::New(context->GetIsolate(), static_cast<enumUndelyingType>(value));
    }
}

template<typename type = int>
type JSToInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context, type defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    return static_cast<type>(value->ToInteger(context).ToLocalChecked()->Int32Value(context).ToChecked());
}

template<typename type = unsigned int>
type JSToUInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context, type defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    return static_cast<type>(value->ToInteger(context).ToLocalChecked()->Uint32Value(context).ToChecked());
}

template<typename type = int>
type JSToInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return {};
    }

    return static_cast<type>(value->ToInteger(context).ToLocalChecked()->Int32Value(context).ToChecked());
}

template<typename type = unsigned int>
type JSToUInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return {};
    }

    return static_cast<type>(value->ToInteger(context).ToLocalChecked()->Int32Value(context).ToChecked());
}

template<typename type = int>
v8::Local<v8::Integer> IntToJS(type value, v8::Local<v8::Context> context) {
    return v8::Integer::New(context->GetIsolate(), value);
}

template<typename type = unsigned int>
v8::Local<v8::Integer> UIntToJS(type value, v8::Local<v8::Context> context) {
    return v8::Integer::NewFromUnsigned(context->GetIsolate(), value);
}

template<typename type1 = int, typename type2 = int>
v8::Local<v8::Array> PairIntToJS(Pair<type1, type2> value, v8::Local<v8::Context> context) {
    v8::EscapableHandleScope handle_scope(context->GetIsolate());

    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), 2);

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    // Fill out the values
    array->Set(context, 0, IntToJS<type1>(value.first, context)).Check();
    array->Set(context, 1, IntToJS<type2>(value.second, context)).Check();

    return handle_scope.Escape(array);
}