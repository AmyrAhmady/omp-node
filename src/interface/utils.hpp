#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"

#define ENTER_CONTEXT_SCOPE(info) \
	auto isolate = (info).GetIsolate(); \
	v8::Locker locker(isolate); \
	v8::Isolate::Scope isolateScope(isolate); \
	v8::HandleScope scope(isolate); \
	v8::Local<v8::Context> context = isolate->GetCurrentContext(); \
	v8::Context::Scope contextScope(context);

typedef std::vector<std::pair<std::string, v8::FunctionCallback>> ObjectMethods;

template <class Interface>
v8::Local<v8::Object> InterfaceToObject(Interface *pointer, v8::Local<v8::Context> context, const std::vector<std::pair<std::string, v8::FunctionCallback>>& methods) {
	auto isolate = context->GetIsolate();

	auto objectTemplate = v8::ObjectTemplate::New(isolate);

	objectTemplate->SetInternalFieldCount(1);

	for (auto& entry : methods) {
		objectTemplate->Set(v8::String::NewFromUtf8(isolate, entry.first.c_str(), v8::NewStringType::kNormal).ToLocalChecked(), v8::FunctionTemplate::New(isolate, entry.second));
	}

	auto object = objectTemplate->NewInstance(context).ToLocalChecked();

	object->SetInternalField(0, v8::External::New(isolate, pointer));

	return object;
}

template <class Interface>
Interface *GetContextExternalPointer(const v8::FunctionCallbackInfo<v8::Value> &info) {
	v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast( info.This()->GetInternalField(0) );

	return static_cast<Interface*>( pointer->Value() );
}

float GetFloat(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
int GetInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context);
StringView GetStringView(v8::Local<v8::Value> value, v8::Local<v8::Context> context);