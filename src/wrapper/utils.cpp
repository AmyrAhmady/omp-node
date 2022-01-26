#include "utils.hpp"

float JSToFloat(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (!value->IsNumber()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value must be a number").ToLocalChecked()));
    }

    return static_cast<float>(value->NumberValue(context).ToChecked());
}

int JSToInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (!value->IsNumber()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value must be a number").ToLocalChecked()));
    }

    return static_cast<int>(value->Int32Value(context).ToChecked());
}

StringView JSToStringView(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (!value->IsString()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value must be a string").ToLocalChecked()));
    }

    return StringView(utils::js_to_cstr(isolate, value));
}

bool JSToBool(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (!value->IsBoolean()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value must be a boolean").ToLocalChecked()));
    }

    return value.As<v8::Boolean>()->Value();
}

v8::Local<v8::Number> FloatToJS(float value, v8::Isolate *isolate) {
    return v8::Number::New(isolate, value);
}

v8::Local<v8::Integer> IntToJS(int value, v8::Isolate *isolate) {
    return v8::Integer::New(isolate, value);
}

v8::Local<v8::String> StringViewToJS(StringView str, v8::Isolate *isolate) {
    return v8::String::NewFromUtf8(isolate, str.cbegin(), v8::NewStringType::kNormal, str.size()).ToLocalChecked();
}

v8::Local<v8::Boolean> BoolToJS(bool value, v8::Isolate *isolate) {
    return v8::Boolean::New(isolate, value);
}

v8::Local<v8::Object> PlayerKeyDataToJS(PlayerKeyData &data, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    auto dataTemplate = v8::ObjectTemplate::New(context->GetIsolate());

    dataTemplate->Set(v8::String::NewFromUtf8(isolate, "keys").ToLocalChecked(), v8::Integer::New(isolate, data.keys));
    dataTemplate->Set(v8::String::NewFromUtf8(isolate, "upDown").ToLocalChecked(),
                      v8::Integer::New(isolate, data.upDown));
    dataTemplate->Set(v8::String::NewFromUtf8(isolate, "leftRight").ToLocalChecked(),
                      v8::Integer::New(isolate, data.leftRight));

    auto object = dataTemplate->NewInstance(context).ToLocalChecked();

    return object;
}

HandleStorage *GetContextHandleStorage(const v8::FunctionCallbackInfo<v8::Value> &info) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(info.This()->GetInternalField(0));

    return static_cast<HandleStorage *>( pointer->Value());
}