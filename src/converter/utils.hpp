#pragma once
#include "for_each.hpp"

#define OBJECT_CONVERTER_HANDLE_(Type, name, ToJS, FromJS, ...) \
    auto name##Handle = value.As<v8::Object>()->Get(context, v8::String::NewFromUtf8(isolate, #name).ToLocalChecked());
#define OBJECT_CONVERTER_HANDLE(params) OBJECT_CONVERTER_HANDLE_ params

#define OBJECT_CONVERTER_CHECK_HANDLE_(Type, name, ToJS, FromJS, ...) \
    if (!tryCatch.HasCaught() && (name##Handle.IsEmpty() || name##Handle.ToLocalChecked()->IsNullOrUndefined())) { \
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, #name " field is missing").ToLocalChecked())); \
    }
#define OBJECT_CONVERTER_CHECK_HANDLE(params) OBJECT_CONVERTER_CHECK_HANDLE_ params

#define OBJECT_CONVERTER_CONVERT_(Type, name, ToJS, FromJS, ...) \
    auto name = FromJS(name##Handle.ToLocalChecked(), context);
#define OBJECT_CONVERTER_CONVERT(params) OBJECT_CONVERTER_CONVERT_ params

#define OBJECT_CONVERTER_RETURN_(Type, name, ToJS, FromJS, ...) name,
#define OBJECT_CONVERTER_RETURN(params) OBJECT_CONVERTER_RETURN_ params

#define OBJECT_CONVERTER_TO_JS_SET_(Type, name, ToJS, FromJS, token, ...) object->Set(context, v8::String::NewFromUtf8(isolate, #name).ToLocalChecked(), ToJS(token, context)).Check();

#define OBJECT_CONVERTER_TO_JS_SET__(Type, name, ToJS, FromJS, ...) OBJECT_CONVERTER_TO_JS_SET_(Type, name, ToJS, FromJS, ##__VA_ARGS__, data.name)
#define OBJECT_CONVERTER_TO_JS_SET(params) OBJECT_CONVERTER_TO_JS_SET__ params

#define OBJECT_CONVERTER_DEFINE_TO_JS(Type, ...) \
    v8::Local<v8::Object> Type##ToJS(const Type &data, v8::Local<v8::Context> context) { \
        auto isolate = context->GetIsolate(); \
        auto dataTemplate = v8::ObjectTemplate::New(context->GetIsolate()); \
        auto object = dataTemplate->NewInstance(context).ToLocalChecked(); \
        FOR_EACH(OBJECT_CONVERTER_TO_JS_SET, __VA_ARGS__) \
        return object; \
    }

#define OBJECT_CONVERTER_DEFINE_FROM_JS(Type, defaultValue, ...) \
    Type JSTo##Type(v8::Local<v8::Value> value, v8::Local<v8::Context> context) { \
        auto isolate = context->GetIsolate(); \
        if (!value->IsObject()) { \
            isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, \
                                                                                     "An object is required for " #Type).ToLocalChecked())); \
            return defaultValue; \
        } \
        FOR_EACH(OBJECT_CONVERTER_HANDLE, __VA_ARGS__) \
        v8::TryCatch tryCatch(isolate); \
        FOR_EACH(OBJECT_CONVERTER_CHECK_HANDLE, __VA_ARGS__) \
        if (tryCatch.HasCaught()) { \
            tryCatch.ReThrow(); \
            return defaultValue; \
        } \
        FOR_EACH(OBJECT_CONVERTER_CONVERT, __VA_ARGS__) \
        return { \
            FOR_EACH(OBJECT_CONVERTER_RETURN, __VA_ARGS__) \
        }; \
    }

#define OBJECT_CONVERTER_DEFINE_FROM_JS_CUSTOM(Type, defaultValue, InitializeStructure, ...) \
    Type JSTo##Type(v8::Local<v8::Value> value, v8::Local<v8::Context> context) { \
        auto isolate = context->GetIsolate(); \
        if (!value->IsObject()) { \
            isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, \
                                                                                     "An object is required for " #Type).ToLocalChecked())); \
            return defaultValue; \
        } \
        FOR_EACH(OBJECT_CONVERTER_HANDLE, __VA_ARGS__) \
        v8::TryCatch tryCatch(isolate); \
        FOR_EACH(OBJECT_CONVERTER_CHECK_HANDLE, __VA_ARGS__) \
        if (tryCatch.HasCaught()) { \
            tryCatch.ReThrow(); \
            return defaultValue; \
        } \
        FOR_EACH(OBJECT_CONVERTER_CONVERT, __VA_ARGS__) \
        return InitializeStructure; \
    }

#define OBJECT_CONVERTER_DEFINE(Type, ...) \
    OBJECT_CONVERTER_DEFINE_TO_JS(Type, __VA_ARGS__) \
    OBJECT_CONVERTER_DEFINE_FROM_JS(Type, {}, __VA_ARGS__)

#define OBJECT_CONVERTER_DEFINE_WITH_DEFAULT(Type, defaultValue, ...) \
    OBJECT_CONVERTER_DEFINE_TO_JS(Type, __VA_ARGS__) \
    OBJECT_CONVERTER_DEFINE_FROM_JS(Type, defaultValue, __VA_ARGS__)

#define OBJECT_CONVERTER_DECLARE_TO_JS(Type) v8::Local<v8::Object> Type##ToJS(const Type &data, v8::Local<v8::Context> context);
#define OBJECT_CONVERTER_DECLARE_FROM_JS(Type) Type JSTo##Type(v8::Local<v8::Value> value, v8::Local<v8::Context> context);

// todo: add checking default and missing parameters

#define OBJECT_CONVERTER_DECLARE(Type) \
    OBJECT_CONVERTER_DECLARE_TO_JS(Type) \
    OBJECT_CONVERTER_DECLARE_FROM_JS(Type)
