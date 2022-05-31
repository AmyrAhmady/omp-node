#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include <limits>
#include "../logger.hpp"

Impl::String JSToString(v8::Local<v8::Value> value, v8::Local<v8::Context> context, Impl::String defaultValue);
bool JSToBool(v8::Local<v8::Value> value, v8::Local<v8::Context> context, bool defaultValue);
char JSToChar(v8::Local<v8::Value> value, v8::Local<v8::Context> context, char defaultValue);

Impl::String JSToString(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
bool JSToBool(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
char JSToChar(v8::Local<v8::Value> value, v8::Local<v8::Context> context);

v8::Local<v8::String> StringViewToJS(StringView str, v8::Local<v8::Context> context);
v8::Local<v8::Boolean> BoolToJS(bool value, v8::Local<v8::Context> context);
v8::Local<v8::String> CharToJS(char value, v8::Local<v8::Context> context);

template<typename TargetType, typename SrcType>
inline bool IsInRange(SrcType srcValue) {
    return !(srcValue < std::numeric_limits<TargetType>::lowest() || srcValue > std::numeric_limits<TargetType>::max());
}

template<typename type = float>
type JSToFloat(v8::Local<v8::Value> value, v8::Local<v8::Context> context, type defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    auto srcValue = value->ToNumber(context).ToLocalChecked()->NumberValue(context).ToChecked();

    if (isnan(srcValue)) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Number value is NaN").ToLocalChecked()));
        return {};
    }

    if (isfinite(srcValue) && !IsInRange<type>(srcValue)) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Number value is out of bounds").ToLocalChecked()));
        return {};
    }

    return static_cast<type>(srcValue);
}

template<typename type = float>
type JSToFloat(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return type();
    }

    auto srcValue = value->ToNumber(context).ToLocalChecked()->NumberValue(context).ToChecked();

    if (isnan(srcValue)) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Number value is NaN").ToLocalChecked()));
        return {};
    }

    if (isfinite(srcValue) && !IsInRange<type>(srcValue)) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Number value is out of bounds").ToLocalChecked()));
        return {};
    }

    return static_cast<type>(srcValue);
}

// todo: add checking finiteness
template<typename type = int>
type JSToInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context, type defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    if (!isfinite(value->ToNumber(context).ToLocalChecked()->NumberValue(context).ToChecked())) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Number value is not finite").ToLocalChecked()));
        return {};
    }

    auto srcValue = value->ToInteger(context).ToLocalChecked()->IntegerValue(context).ToChecked();

    if (!IsInRange<type>(srcValue)) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Number value is out of bounds").ToLocalChecked()));
        return {};
    }

    return static_cast<type>(srcValue);
}

template<typename type = unsigned int>
type JSToUInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context, type defaultValue) {
    return JSToInt<type>(value, context, defaultValue);
}

template<typename type = int>
type JSToInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return {};
    }

    if (!isfinite(value->ToNumber(context).ToLocalChecked()->NumberValue(context).ToChecked())) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Number value is not finite").ToLocalChecked()));
        return {};
    }

    auto srcValue = value->ToInteger(context).ToLocalChecked()->IntegerValue(context).ToChecked();

    if (!IsInRange<type>(srcValue)) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Number value is out of bounds").ToLocalChecked()));
        return {};
    }

    return static_cast<type>(srcValue);
}

template<typename type = unsigned int>
type JSToUInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    return JSToInt<type>(value, context);
}

template<typename type = float>
v8::Local<v8::Number> FloatToJS(type value, v8::Local<v8::Context> context) {
    return v8::Number::New(context->GetIsolate(), value);
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

template<typename Enum>
Enum JSToEnum(v8::Local<v8::Value> value, v8::Local<v8::Context> context, Enum defaultValue) {
    if (value->IsUndefined()) {
        return defaultValue;
    }

    using enumUnderlyingType = typename std::underlying_type<Enum>::type;

    return static_cast<Enum>(JSToInt<enumUnderlyingType>(value, context));
}

template<typename Enum>
Enum JSToEnum(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return {};
    }

    using enumUnderlyingType = typename std::underlying_type<Enum>::type;

    return static_cast<Enum>(JSToInt<enumUnderlyingType>(value, context));
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