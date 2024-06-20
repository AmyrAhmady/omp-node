#pragma once
#include "node.h"
#include "v8.h"
#include "json.hpp"
#include "ompcapi.h"
#pragma warning(disable : 4312)
// Parts of this file is taken from altv-js-module, thanks to altv team
// https://github.com/altmp/altv-js-module

namespace helpers
{
template <typename T>
using CopyablePersistent = v8::Persistent<T, v8::CopyablePersistentTraits<T>>;

inline void Throw(v8::Isolate* isolate, const Impl::String& msg)
{
	isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, msg.data(), v8::NewStringType::kNormal, (int)msg.size()).ToLocalChecked()));
}

inline bool SafeToBoolean(v8::Local<v8::Value> val, v8::Isolate* isolate, bool& out)
{
	out = val->ToBoolean(isolate)->Value();
	return true;
}

inline bool SafeToUInt64(v8::Local<v8::Value> val, v8::Local<v8::Context> ctx, uint64_t& out)
{
	auto check = val->ToInteger(ctx);
	if (check.IsEmpty() || check.ToLocalChecked()->Value() < 0)
		return false; // Check for negative values
	v8::MaybeLocal maybeVal = val->ToBigInt(ctx);
	if (maybeVal.IsEmpty())
		return false;
	out = maybeVal.ToLocalChecked()->Uint64Value();
	return true;
}

inline bool SafeToInt64(v8::Local<v8::Value> val, v8::Local<v8::Context> ctx, int64_t& out)
{
	v8::MaybeLocal maybeVal = val->ToBigInt(ctx);
	if (maybeVal.IsEmpty())
		return false;
	out = maybeVal.ToLocalChecked()->Int64Value();
	return true;
}

inline bool SafeToUInt32(v8::Local<v8::Value> val, v8::Local<v8::Context> ctx, uint32_t& out)
{
	auto check = val->ToInteger(ctx);
	if (check.IsEmpty() || check.ToLocalChecked()->Value() < 0)
		return false; // Check for negative values
	v8::MaybeLocal maybeVal = val->ToUint32(ctx);
	if (maybeVal.IsEmpty())
		return false;
	out = maybeVal.ToLocalChecked()->Value();
	return true;
}

inline bool SafeToUInt8(v8::Local<v8::Value> val, v8::Local<v8::Context> ctx, uint8_t& out)
{
	auto check = val->ToInteger(ctx);
	if (check.IsEmpty() || check.ToLocalChecked()->Value() < 0)
		return false; // Check for negative values
	v8::MaybeLocal maybeVal = val->ToUint32(ctx);
	if (maybeVal.IsEmpty())
		return false;
	out = static_cast<uint8_t>(maybeVal.ToLocalChecked()->Value());
	return true;
}

inline bool SafeToInt32(v8::Local<v8::Value> val, v8::Local<v8::Context> ctx, int32_t& out)
{
	v8::MaybeLocal maybeVal = val->ToInt32(ctx);
	if (maybeVal.IsEmpty())
		return false;
	out = maybeVal.ToLocalChecked()->Value();
	return true;
}

inline bool SafeToFloat(v8::Local<v8::Value> val, v8::Local<v8::Context> ctx, float& out)
{
	v8::MaybeLocal maybeVal = val->ToNumber(ctx);
	if (maybeVal.IsEmpty())
		return false;
	out = static_cast<float>(maybeVal.ToLocalChecked()->Value());
	return true;
}

inline bool SafeToString(v8::Local<v8::Value> val, v8::Isolate* isolate, v8::Local<v8::Context> ctx, Impl::String& out)
{
	v8::MaybeLocal maybeVal = val->ToString(ctx);
	if (maybeVal.IsEmpty())
		return false;
	out = *v8::String::Utf8Value(isolate, maybeVal.ToLocalChecked());
	return true;
}

inline v8::Local<v8::Value> JsonToV8(v8::Isolate* isolate, const nlohmann::json& j)
{
	if (j.is_null())
	{
		return v8::Null(isolate);
	}
	else if (j.is_boolean())
	{
		return v8::Boolean::New(isolate, j.get<bool>());
	}
	else if (j.is_number())
	{
		return v8::Number::New(isolate, j.get<double>());
	}
	else if (j.is_string())
	{
		return v8::String::NewFromUtf8(isolate, j.get<Impl::String>().c_str(), v8::NewStringType::kNormal).ToLocalChecked();
	}
	else if (j.is_array())
	{
		v8::Local<v8::Array> arr = v8::Array::New(isolate, j.size());
		for (size_t i = 0; i < j.size(); ++i)
		{
			arr->Set(isolate->GetCurrentContext(), static_cast<uint32_t>(i), JsonToV8(isolate, j[i])).Check();
		}
		return arr;
	}
	else if (j.is_object())
	{
		v8::Local<v8::Object> obj = v8::Object::New(isolate);
		for (nlohmann::json::const_iterator it = j.begin(); it != j.end(); ++it)
		{
			obj->Set(isolate->GetCurrentContext(),
				   v8::String::NewFromUtf8(isolate, it.key().c_str(), v8::NewStringType::kNormal).ToLocalChecked(),
				   JsonToV8(isolate, it.value()))
				.Check();
		}
		return obj;
	}
	else
	{
		return v8::Undefined(isolate);
	}
}

inline v8::Local<v8::String> JSValue(v8::Isolate* isolate, const CAPIStringView& val)
{
	return v8::String::NewFromUtf8(isolate, val.data, v8::NewStringType::kNormal, val.len).ToLocalChecked();
}

inline v8::Local<v8::String> JSValue(v8::Isolate* isolate, const char* val)
{
	return v8::String::NewFromUtf8(isolate, val).ToLocalChecked();
}

inline v8::Local<v8::String> JSValue(v8::Isolate* isolate, const Impl::String& val)
{
	return v8::String::NewFromUtf8(isolate, val.c_str(), v8::NewStringType::kNormal, (int)val.size()).ToLocalChecked();
}

inline v8::Local<v8::Boolean> JSValue(v8::Isolate* isolate, bool val)
{
	return v8::Boolean::New(isolate, val);
}

inline v8::Local<v8::Number> JSValue(v8::Isolate* isolate, float val)
{
	return v8::Number::New(isolate, val);
}

inline v8::Local<v8::Integer> JSValue(v8::Isolate* isolate, int32_t val)
{
	return v8::Integer::New(isolate, val);
}

inline v8::Local<v8::Integer> JSValue(v8::Isolate* isolate, uint32_t val)
{
	return v8::Integer::NewFromUnsigned(isolate, val);
}

inline v8::Local<v8::BigInt> JSValue(v8::Isolate* isolate, int64_t val)
{
	return v8::BigInt::New(isolate, val);
}

inline v8::Local<v8::BigInt> JSValue(v8::Isolate* isolate, uint64_t val)
{
	return v8::BigInt::NewFromUnsigned(isolate, val);
}
}

#define V8_ISOLATE_SCOPE(isolate)             \
	v8::Locker locker(isolate);               \
	v8::Isolate::Scope isolateScope(isolate); \
	v8::HandleScope handleScope(isolate)

#define V8_CHECK_RETN(a, b, c)        \
	if (!(a))                         \
	{                                 \
		helpers::Throw(isolate, (b)); \
		return c;                     \
	}

#define V8_CHECK(a, b) V8_CHECK_RETN(a, b, )

#define V8_CHECK_ARGS_LEN(count) V8_CHECK(info.Length() == (count), std::to_string(count) + " arguments expected")

#define V8_TO_BOOLEAN(v8Val, val) \
	bool val;                     \
	V8_CHECK(helpers::SafeToBoolean((v8Val), isolate, val), "Failed to convert value to boolean")

#define V8_TO_FLOAT(v8Val, val) \
	float val;                  \
	V8_CHECK(helpers::SafeToFloat((v8Val), ctx, val), "Failed to convert value to float")

#define V8_TO_INT64(v8Val, val) \
	int64_t val;                \
	V8_CHECK(helpers::SafeToInt64((v8Val), ctx, val), "Failed to convert value to 64bit integer")

#define V8_TO_UINT64(v8Val, val) \
	uint64_t val;                \
	V8_CHECK(helpers::SafeToUInt64((v8Val), ctx, val), "Failed to convert value to unsigned 64bit integer")

#define V8_TO_INT32(v8Val, val) \
	int32_t val;                \
	V8_CHECK(helpers::SafeToInt32((v8Val), ctx, val), "Failed to convert value to 32bit integer")

#define V8_TO_UINT32(v8Val, val) \
	uint32_t val;                \
	V8_CHECK(helpers::SafeToUInt32((v8Val), ctx, val), "Failed to convert value to unsigned 32bit integer")

#define V8_TO_UINT32(v8Val, val) \
	uint32_t val;                \
	V8_CHECK(helpers::SafeToUInt32((v8Val), ctx, val), "Failed to convert value to unsigned 32bit integer")

#define V8_TO_UINT8(v8Val, val) \
	uint8_t val;                \
	V8_CHECK(helpers::SafeToUInt8((v8Val), ctx, val), "Failed to convert value to unsigned 8bit integer")

#define V8_TO_STRING(v8Val, val) \
	Impl::String val;            \
	V8_CHECK(helpers::SafeToString((v8Val), isolate, ctx, val), "Failed to convert value to string")

#define V8_TO_UINTPTR(v8Val, val)                                            \
	int64_t val##_64;                                                        \
	int32_t val##_32;                                                        \
	bool result_##val = false;                                               \
	void* val;                                                               \
	if (sizeof(uintptr_t) == 8)                                              \
	{                                                                        \
		result_##val = helpers::SafeToInt64((v8Val), ctx, val##_64);         \
		V8_CHECK(result_##val, "Failed to convert value to integer pointer") \
		val = (void*)(val##_64);                                             \
	}                                                                        \
	else                                                                     \
	{                                                                        \
		result_##val = helpers::SafeToInt32((v8Val), ctx, val##_32);         \
		V8_CHECK(result_##val, "Failed to convert value to integer pointer") \
		val = (void*)(val##_32);                                             \
	}
