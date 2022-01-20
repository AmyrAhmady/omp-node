#include "utils.hpp"

float GetFloat(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
	auto isolate = context->GetIsolate();

	if (!value->IsNumber()) {
		isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "A value must be a number").ToLocalChecked()));
	}

	return static_cast<float>(value->NumberValue(context).ToChecked());
}

int GetInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
	auto isolate = context->GetIsolate();

	if (!value->IsNumber()) {
		isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "A value must be a number").ToLocalChecked()));
	}

	return static_cast<int>(value->Int32Value(context).ToChecked());
}

StringView GetStringView(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
	auto isolate = context->GetIsolate();

	if (!value->IsString()) {
		isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "A value must be a string").ToLocalChecked()));
	}

	return StringView(utils::js_to_cstr(isolate, value));
}