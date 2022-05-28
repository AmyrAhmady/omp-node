#pragma once
#include "v8.h"

template<class EntityType>
EntityType *JSToEntity(v8::Local<v8::Value> value, v8::Local<v8::Context> context, EntityType *defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    if (value->IsNull()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Object must not be null").ToLocalChecked()));

        return nullptr;
    }

    const auto handle = value.As<v8::Object>();

    if (handle->InternalFieldCount() == 0) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Object is not an OMP structure").ToLocalChecked()));

        return nullptr;
    }

    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(handle->GetInternalField(0));

    return static_cast<EntityType *>(pointer->Value());
}

template<class EntityType>
EntityType *JSToEntity(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsNullOrUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Object must not be null or undefined").ToLocalChecked()));

        return nullptr;
    }

    const auto handle = value.As<v8::Object>();

    if (handle->InternalFieldCount() == 0) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Object is not an OMP structure").ToLocalChecked()));

        return nullptr;
    }

    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(handle->GetInternalField(0));

    return static_cast<EntityType *>(pointer->Value());
}

template<class EntityType>
EntityType &JSToEntityRef(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    EntityType *defaultValue = nullptr;

    if (value->IsNullOrUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Object must not be null or undefined").ToLocalChecked()));

        return *defaultValue;
    }

    const auto handle = value.As<v8::Object>();

    if (handle->InternalFieldCount() == 0) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Object is not an OMP structure").ToLocalChecked()));

        return *defaultValue;
    }

    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(handle->GetInternalField(0));

    auto pointerValue = static_cast<EntityType *>(pointer->Value());

    return *pointerValue;
}

template<class EntityType>
v8::Local<v8::Value> EntityToJS(EntityType &actor, v8::Local<v8::Context> context) {
    auto ext = GetHandleStorageExtension(&actor);

    return ext->get();
}

template<class EntityType>
v8::Local<v8::Value> EntityToJS(EntityType *actor, v8::Local<v8::Context> context) {
    if (actor == nullptr) {
        return v8::Null(context->GetIsolate());
    }

    auto ext = GetHandleStorageExtension(actor);

    return ext->get();
}