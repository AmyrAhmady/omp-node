#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"

#define ENTER_FUNCTION_CALLBACK(info) \
	auto isolate = (info).GetIsolate(); \
	v8::Locker locker(isolate); \
	v8::Isolate::Scope isolateScope(isolate); \
	v8::HandleScope scope(isolate); \
	v8::Local<v8::Context> context = isolate->GetCurrentContext(); \
	v8::Context::Scope contextScope(context);

struct HandleStorage {
    FlatHashMap<void*, v8::UniquePersistent<v8::Value>*> storageMap;

    template<typename Key>
    void set(Key *key, v8::UniquePersistent<v8::Value>* value) {
        storageMap.emplace(key, value);
    }

    template<typename Key>
    v8::UniquePersistent<v8::Value> *get(Key* key) {
        auto pair = storageMap.find(key);

        if (pair != storageMap.end()) {
            return pair->second;
        }

        return nullptr; // todo: don't return nullptr
    }

    template<typename Key>
    void remove(Key* key) {
        storageMap.erase(key);
    }
};

typedef std::vector<std::pair<std::string, v8::FunctionCallback>> ObjectMethods;
typedef std::vector<std::tuple<std::string, v8::FunctionCallback, v8::FunctionCallback>> ObjectAccessors;

template <class Interface>
v8::Local<v8::Object> InterfaceToObject(HandleStorage &storage, Interface *pointer, v8::Local<v8::Context> context, const ObjectMethods& methods) {
	auto isolate = context->GetIsolate();

	auto objectTemplate = v8::ObjectTemplate::New(isolate);

	objectTemplate->SetInternalFieldCount(2);

	for (auto& entry : methods) {
		objectTemplate->Set(v8::String::NewFromUtf8(isolate, entry.first.c_str(), v8::NewStringType::kNormal).ToLocalChecked(), v8::FunctionTemplate::New(isolate, entry.second));
	}

	auto object = objectTemplate->NewInstance(context).ToLocalChecked();

    object->SetInternalField(0, v8::External::New(isolate, &storage));
	object->SetInternalField(1, v8::External::New(isolate, pointer));

	return object;
}

template <class Interface>
v8::Local<v8::Object> MutableToObject(HandleStorage &storage, Interface *pointer, v8::Local<v8::Context> context, const ObjectAccessors& accessors) {
	auto isolate = context->GetIsolate();

	auto objectTemplate = v8::ObjectTemplate::New(isolate);

	objectTemplate->SetInternalFieldCount(2);

	for (auto& entry : accessors) {
        objectTemplate->SetAccessorProperty(v8::String::NewFromUtf8(isolate, std::get<0>(entry).c_str()).ToLocalChecked(), v8::FunctionTemplate::New(isolate, std::get<1>(entry)), v8::FunctionTemplate::New(isolate, std::get<2>(entry)));
	}

	auto object = objectTemplate->NewInstance(context).ToLocalChecked();

    object->SetInternalField(0, v8::External::New(isolate, &storage));
    object->SetInternalField(1, v8::External::New(isolate, pointer));

	return object;
}

HandleStorage *GetContextHandleStorage(const v8::FunctionCallbackInfo<v8::Value> &info);

template <class Interface>
Interface *GetContextExternalPointer(const v8::FunctionCallbackInfo<v8::Value> &info) {
	v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast( info.This()->GetInternalField(1) );

	return static_cast<Interface*>( pointer->Value() );
}

float JSToFloat(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
int JSToInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
StringView JSToStringView(v8::Local<v8::Value> value, v8::Local<v8::Context> context);

v8::Local<v8::Number> FloatToJS(float value, v8::Isolate *isolate);
v8::Local<v8::Integer> IntToJS(int value, v8::Isolate *isolate);
v8::Local<v8::String> StringViewToJS(StringView str, v8::Isolate *isolate);

v8::Local<v8::Object> PlayerKeyDataToJS(PlayerKeyData &data, v8::Local<v8::Context>);
