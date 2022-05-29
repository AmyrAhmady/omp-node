#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "../logger.hpp"
#include "methods.hpp"
#include "handlers.hpp"
#include "../converter/find_function.hpp"

#define ENTER_FUNCTION_CALLBACK(info) \
    auto isolate = (info).GetIsolate(); \
    v8::Locker locker(isolate); \
    v8::Isolate::Scope isolateScope(isolate); \
    v8::HandleScope scope(isolate); \
    v8::Local<v8::Context> context = isolate->GetCurrentContext(); \
    v8::Context::Scope contextScope(context);

#define ENTER_HANDLER(isolate, handler) \
    v8::Locker locker(isolate); \
    v8::Isolate::Scope isolateScope(isolate); \
    v8::HandleScope scope(isolate); \
    auto func = handler.Get(isolate); \
    v8::Local<v8::Context> context = func->GetCreationContext().ToLocalChecked(); \
    v8::Context::Scope contextScope(context);

static const UID HandleStorage_UID = UID(0xd42b91d86d0c7b30);
struct IHandleStorage : public IExtension {
    PROVIDE_EXT_UID(HandleStorage_UID);

    v8::Isolate *isolate;
    v8::UniquePersistent<v8::Value> storedValue;

    IHandleStorage(v8::Isolate *isolate, v8::Local<v8::Value> value);

    v8::Local<v8::Value> get();

    void freeExtension() override;

    void reset() override;
};

#define CREATE_HANDLE_STORAGE_EXTENSION(ID, Type) \
    static const UID Type##_UID = UID(ID); \
    struct Type : public IHandleStorage { \
        PROVIDE_EXT_UID(Type##_UID); \
        Type(v8::Isolate *isolate, v8::Local<v8::Value> value) : IHandleStorage(isolate, value) { \
            L_DEBUG << #Type; \
        } \
    };

CREATE_HANDLE_STORAGE_EXTENSION(0x05be1bbe879280ee, EventDispatcherHandleStorage)
CREATE_HANDLE_STORAGE_EXTENSION(0x74b01b92d5207574, PoolEventDispatcherHandleStorage)

IHandleStorage *GetHandleStorageExtension(IExtensible *extensible);

typedef std::vector<std::pair<std::string, v8::FunctionCallback>> ObjectMethods;
typedef std::vector<std::tuple<std::string, v8::FunctionCallback, v8::FunctionCallback>> ObjectAccessors;

template<class Interface>
v8::Local<v8::Object> InterfaceToObject(Interface *pointer,
                                        v8::Local<v8::Context> context,
                                        const ObjectMethods &methods) {
    auto isolate = context->GetIsolate();

    auto objectTemplate = v8::ObjectTemplate::New(isolate);

    objectTemplate->SetInternalFieldCount(1);

    for (auto &entry: methods) {
        objectTemplate->Set(v8::String::NewFromUtf8(isolate,
                                                    entry.first.c_str(),
                                                    v8::NewStringType::kNormal).ToLocalChecked(),
                            v8::FunctionTemplate::New(isolate, entry.second));
    }

    auto object = objectTemplate->NewInstance(context).ToLocalChecked();

    object->SetInternalField(0, v8::External::New(isolate, pointer));

    return object;
}

template<class Interface>
v8::Local<v8::Object> MutableToObject(Interface *pointer,
                                      v8::Local<v8::Context> context,
                                      const ObjectAccessors &accessors) {
    auto isolate = context->GetIsolate();

    auto objectTemplate = v8::ObjectTemplate::New(isolate);

    objectTemplate->SetInternalFieldCount(1);

    for (auto &entry: accessors) {
        objectTemplate->SetAccessorProperty(v8::String::NewFromUtf8(isolate,
                                                                    std::get<0>(entry).c_str()).ToLocalChecked(),
                                            v8::FunctionTemplate::New(isolate, std::get<1>(entry)),
                                            v8::FunctionTemplate::New(isolate, std::get<2>(entry)));
    }

    auto object = objectTemplate->NewInstance(context).ToLocalChecked();

    object->SetInternalField(0, v8::External::New(isolate, pointer));

    return object;
}

template<class Interface>
Interface *GetContextExternalPointer(const v8::FunctionCallbackInfo<v8::Value> &info) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(info.This()->GetInternalField(0));

    return static_cast<Interface *>( pointer->Value());
}
