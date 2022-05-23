#pragma once
#include "for_each.hpp"

#define OBJECT_CONVERTER_HANDLE_(Type, name, ToJS, FromJS) \
    auto name##Handle = value.As<v8::Object>()->Get(context, v8::String::NewFromUtf8(isolate, #name).ToLocalChecked());
#define OBJECT_CONVERTER_HANDLE(params) OBJECT_CONVERTER_HANDLE_ params

#define OBJECT_CONVERTER_CHECK_HANDLE_(Type, name, ToJS, FromJS) \
    if (name##Handle.IsEmpty() || name##Handle.ToLocalChecked()->IsUndefined()) {                               \
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, #name " field is missing").ToLocalChecked())); \
        return {};                                              \
    }
#define OBJECT_CONVERTER_CHECK_HANDLE(params) OBJECT_CONVERTER_CHECK_HANDLE_ params

#define OBJECT_CONVERTER_CONVERT_(Type, name, ToJS, FromJS) \
    auto name = FromJS(name##Handle.ToLocalChecked(), context);
#define OBJECT_CONVERTER_CONVERT(params) OBJECT_CONVERTER_CONVERT_ params

#define OBJECT_CONVERTER_RETURN_(Type, name, ToJS, FromJS) name,
#define OBJECT_CONVERTER_RETURN(params) OBJECT_CONVERTER_RETURN_ params

#define OBJECT_CONVERTER_TO_JS_SET_(Type, name, ToJS, FromJS) object->Set(context, v8::String::NewFromUtf8(isolate, #name).ToLocalChecked(), ToJS(data.name, context)).Check();
#define OBJECT_CONVERTER_TO_JS_SET(params) OBJECT_CONVERTER_TO_JS_SET_ params

#define OBJECT_CONVERTER_DEFINE(Type, ...) \
    Type JSTo##Type(v8::Local<v8::Value> value, v8::Local<v8::Context> context) { \
        auto isolate = context->GetIsolate(); \
        if (!value->IsObject()) { \
            isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, \
                                                                                     "An object is required").ToLocalChecked())); \
            return {}; \
        }                                   \
        FOR_EACH(OBJECT_CONVERTER_HANDLE, __VA_ARGS__)                                                \
        FOR_EACH(OBJECT_CONVERTER_CHECK_HANDLE, __VA_ARGS__) \
        FOR_EACH(OBJECT_CONVERTER_CONVERT, __VA_ARGS__)                                               \
        return { \
            FOR_EACH(OBJECT_CONVERTER_RETURN, __VA_ARGS__) \
        }; \
    }                                      \
    v8::Local<v8::Object> Type##ToJS(const Type &data, v8::Local<v8::Context> context) { \
        auto isolate = context->GetIsolate(); \
        auto dataTemplate = v8::ObjectTemplate::New(context->GetIsolate()); \
        auto object = dataTemplate->NewInstance(context).ToLocalChecked();        \
        FOR_EACH(OBJECT_CONVERTER_TO_JS_SET, __VA_ARGS__)                                   \
        return object; \
    }
// todo: add checking default and missing parameters

#define OBJECT_CONVERTER_DECLARE(Type) \
    Type JSTo##Type(v8::Local<v8::Value> value, v8::Local<v8::Context> context);                               \
    v8::Local<v8::Object> Type##ToJS(const Type &data, v8::Local<v8::Context> context);
