#include "primitive.hpp"

float JSToFloat(v8::Local<v8::Value> value, v8::Local<v8::Context> context, float defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    return static_cast<float>(value->ToNumber(context).ToLocalChecked()->NumberValue(context).ToChecked());
}

Impl::String JSToString(v8::Local<v8::Value> value, v8::Local<v8::Context> context, Impl::String defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    return utils::js_to_string(isolate, value);
}

bool JSToBool(v8::Local<v8::Value> value, v8::Local<v8::Context> context, bool defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    return value->ToBoolean(isolate)->Value();
}

char JSToChar(v8::Local<v8::Value> value, v8::Local<v8::Context> context, char defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    v8::String::Utf8Value jsString(isolate, value);

    if (jsString.length() != 1) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "String must contain only one character").ToLocalChecked()));
        return {};
    }

    auto cstr = *jsString;

    return cstr[0];
}

float JSToFloat(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return float();
    }

    return static_cast<float>(value->ToNumber(context).ToLocalChecked()->NumberValue(context).ToChecked());
}

Impl::String JSToString(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return Impl::String();
    }

    return utils::js_to_string(isolate, value);
}

bool JSToBool(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return bool();
    }

    return value->ToBoolean(isolate)->Value();
}

char JSToChar(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return {};
    }

    v8::String::Utf8Value jsString(isolate, value);

    if (jsString.length() != 1) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "String must contain only one character").ToLocalChecked()));
        return {};
    }

    auto cstr = *jsString;

    return cstr[0];
}

v8::Local<v8::Number> FloatToJS(float value, v8::Local<v8::Context> context) {
    return v8::Number::New(context->GetIsolate(), value);
}

v8::Local<v8::String> StringViewToJS(StringView str, v8::Local<v8::Context> context) {
    return v8::String::NewFromUtf8(context->GetIsolate(),
                                   str.data(),
                                   v8::NewStringType::kNormal,
                                   str.size()).ToLocalChecked();
}

v8::Local<v8::Boolean> BoolToJS(bool value, v8::Local<v8::Context> context) {
    return v8::Boolean::New(context->GetIsolate(), value);
}

v8::Local<v8::String> CharToJS(char letter, v8::Local<v8::Context> context) {
    std::string str(1, letter);

    return v8::String::NewFromUtf8(context->GetIsolate(),
                                   str.c_str(),
                                   v8::NewStringType::kNormal,
                                   str.size()).ToLocalChecked();
}