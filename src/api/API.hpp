#pragma once

#include <v8.h>
#include "omp-node.hpp"
#include "ompcapi.h"

using IntRef = int*;
using FloatRef = float*;
using BoolRef = bool*;
using UInt8Ref = uint8_t*;
using UInt16Ref = uint16_t*;
using UInt32Ref = uint32_t*;
using OutputStringViewPtr = CAPIStringView*;
using OutputStringBufferPtr = CAPIStringBuffer*;

#define SPLIT_IntRef LPAREN IntRef COMMA
#define SPLIT_FloatRef LPAREN FloatRef COMMA
#define SPLIT_BoolRef LPAREN BoolRef COMMA
#define SPLIT_UInt8Ref LPAREN UInt8Ref COMMA
#define SPLIT_UInt16Ref LPAREN UInt16Ref COMMA
#define SPLIT_UInt32Ref LPAREN UInt32Ref COMMA
#define SPLIT_OutputStringViewPtr LPAREN OutputStringViewPtr COMMA
#define SPLIT_OutputStringBufferPtr LPAREN OutputStringBufferPtr COMMA

#define V8_TO_IntRef(info, var) int var
#define V8_TO_FloatRef(info, var) float var
#define V8_TO_BoolRef(info, var) bool var
#define V8_TO_UInt32Ref(info, var) uint32_t var
#define V8_TO_UInt16Ref(info, var) uint16_t var
#define V8_TO_UInt8Ref(info, var) uint8_t var
#define V8_TO_OutputStringViewPtr(info, var) \
	CAPIStringView var { 0, nullptr }
#define V8_TO_OutputStringBufferPtr(info, var) \
	CAPIStringBuffer var { 0, nullptr }

#define VAR_TO_PASS_IntRef(a) &a
#define VAR_TO_PASS_FloatRef(a) &a
#define VAR_TO_PASS_BoolRef(a) &a
#define VAR_TO_PASS_UInt32Ref(a) &a
#define VAR_TO_PASS_UInt16Ref(a) &a
#define VAR_TO_PASS_UInt8Ref(a) &a
#define VAR_TO_PASS_OutputStringViewPtr(a) &a
#define VAR_TO_PASS_OutputStringBufferPtr(a) &a

#define CREATE_FUNCTION_SIG_ARG_IMPL_IntRef(a) IntRef a
#define CREATE_FUNCTION_SIG_ARG_IMPL_FloatRef(a) FloatRef a
#define CREATE_FUNCTION_SIG_ARG_IMPL_BoolRef(a) BoolRef a
#define CREATE_FUNCTION_SIG_ARG_IMPL_UInt32Ref(a) UInt32Ref a
#define CREATE_FUNCTION_SIG_ARG_IMPL_UInt16Ref(a) UInt16Ref a
#define CREATE_FUNCTION_SIG_ARG_IMPL_UInt8Ref(a) UInt8Ref a
#define CREATE_FUNCTION_SIG_ARG_IMPL_OutputStringViewPtr(a) OutputStringViewPtr a
#define CREATE_FUNCTION_SIG_ARG_IMPL_OutputStringBufferPtr(a) OutputStringBufferPtr a

#define CAST_TYPE_FOR_RETURN_IntRef *
#define CAST_TYPE_FOR_RETURN_FloatRef *
#define CAST_TYPE_FOR_RETURN_BoolRef *
#define CAST_TYPE_FOR_RETURN_UInt32Ref *
#define CAST_TYPE_FOR_RETURN_UInt16Ref *
#define CAST_TYPE_FOR_RETURN_UInt8Ref *
#define CAST_TYPE_FOR_RETURN_OutputStringViewPtr(x) Impl::String(x->data, x->len)
#define CAST_TYPE_FOR_RETURN_OutputStringBufferPtr(x) Impl::String(x.data, x.len)

// group: name for javascript api group
// name: name for javascript api
#define DECLARE_API(group, name, ...)                                                                                                                   \
	class OMP_NODE_API_##group##_##name                                                                                                                 \
	{                                                                                                                                                   \
	public:                                                                                                                                             \
		OMP_NODE_API_##group##_##name()                                                                                                                 \
		{                                                                                                                                               \
			APIManager::Instance().Register(#group, #name, &Call_internal);                                                                             \
		}                                                                                                                                               \
                                                                                                                                                        \
		static void Call_internal(const v8::FunctionCallbackInfo<v8::Value>& info)                                                                      \
		{                                                                                                                                               \
			v8::Isolate* isolate = info.GetIsolate();                                                                                                   \
			v8::Local<v8::Context> ctx = isolate->GetEnteredOrMicrotaskContext();                                                                       \
                                                                                                                                                        \
			auto core = Runtime::Instance().GetCore();                                                                                                  \
                                                                                                                                                        \
			V8_CHECK_ARGS_LEN(EVAL(OMP_NODE__NUM_ARGS(__VA_ARGS__)));                                                                                   \
                                                                                                                                                        \
			GENERATE_PARAMS_TO_DECLARE_VARS(__VA_ARGS__)                                                                                                \
                                                                                                                                                        \
			auto ret = Call_external(GENERATE_PARAMS_TO_USE_IN_FUNCTION_CALL(__VA_ARGS__) info);                                                        \
                                                                                                                                                        \
			info.GetReturnValue().Set(helpers::JsonToV8(isolate, ret));                                                                                 \
		}                                                                                                                                               \
                                                                                                                                                        \
	private:                                                                                                                                            \
		static const nlohmann::json Call_external(GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG(__VA_ARGS__) const v8::FunctionCallbackInfo<v8::Value>& info); \
	} OMP_NODE_API_##group##_##name##_instance;                                                                                                         \
                                                                                                                                                        \
	const nlohmann::json OMP_NODE_API_##group##_##name ::Call_external(GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG(__VA_ARGS__) const v8::FunctionCallbackInfo<v8::Value>& info)

// group: name for javascript api group
// name: name for javascript api
// argnum: argument count
#define DECLARE_API_ARGNUM(group, name, argnum, ...)                                                                                                    \
	class OMP_NODE_API_##group##_##name                                                                                                                 \
	{                                                                                                                                                   \
	public:                                                                                                                                             \
		OMP_NODE_API_##group##_##name()                                                                                                                 \
		{                                                                                                                                               \
			APIManager::Instance().Register(#group, #name, &Call_internal);                                                                             \
		}                                                                                                                                               \
                                                                                                                                                        \
		static void Call_internal(const v8::FunctionCallbackInfo<v8::Value>& info)                                                                      \
		{                                                                                                                                               \
			v8::Isolate* isolate = info.GetIsolate();                                                                                                   \
			v8::Local<v8::Context> ctx = isolate->GetEnteredOrMicrotaskContext();                                                                       \
                                                                                                                                                        \
			auto core = Runtime::Instance().GetCore();                                                                                                  \
                                                                                                                                                        \
			V8_CHECK_ARGS_LEN(argnum);                                                                                                                  \
                                                                                                                                                        \
			GENERATE_PARAMS_TO_DECLARE_VARS(__VA_ARGS__)                                                                                                \
                                                                                                                                                        \
			auto ret = Call_external(GENERATE_PARAMS_TO_USE_IN_FUNCTION_CALL(__VA_ARGS__) info);                                                        \
                                                                                                                                                        \
			info.GetReturnValue().Set(helpers::JsonToV8(isolate, ret));                                                                                 \
		}                                                                                                                                               \
                                                                                                                                                        \
	private:                                                                                                                                            \
		static const nlohmann::json Call_external(GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG(__VA_ARGS__) const v8::FunctionCallbackInfo<v8::Value>& info); \
	} OMP_NODE_API_##group##_##name##_instance;                                                                                                         \
                                                                                                                                                        \
	const nlohmann::json OMP_NODE_API_##group##_##name ::Call_external(GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG(__VA_ARGS__) const v8::FunctionCallbackInfo<v8::Value>& info)
