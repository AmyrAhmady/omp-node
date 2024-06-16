#pragma once
#include <string>
#include <v8.h>
#include "../helpers/v8.hpp"

using IntRef = int*;
using FloatRef = float*;
using BoolRef = bool*;
using UInt8Ref = uint8_t*;
using UInt32Ref = uint32_t*;
using OutputStringViewPtr = CAPIStringView*;
using StringCharPtr = const char*;
using objectPtr = void*;

// splitter of given arg type of name
#define LPAREN (
#define RPAREN )
#define COMMA ,

#define CAT2(L, R) CAT2_(L, R)
#define CAT2_(L, R) L##R
#define EXPAND2(...) __VA_ARGS__

#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a##__VA_ARGS__

#define EMPTY()
#define DEFER(id) id EMPTY()
#define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()
#define EXPAND(...) __VA_ARGS__

#define EVAL(...) EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL1(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL2(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL3(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
#define EVAL4(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
#define EVAL5(...) __VA_ARGS__

#define SPLIT(OP, D) EXPAND2(OP CAT2(SPLIT_, D) RPAREN)
#define SPLIT_INDEX(OP, D, idx) EXPAND2(OP CAT2(SPLIT_, D) COMMA idx RPAREN)

#define SPLIT_int LPAREN int COMMA
#define SPLIT_uint32_t LPAREN uint32_t COMMA
#define SPLIT_uint8_t LPAREN uint8_t COMMA
#define SPLIT_bool LPAREN bool COMMA
#define SPLIT_char LPAREN char COMMA
#define SPLIT_float LPAREN float COMMA
#define SPLIT_IntRef LPAREN IntRef COMMA
#define SPLIT_FloatRef LPAREN FloatRef COMMA
#define SPLIT_BoolRef LPAREN BoolRef COMMA
#define SPLIT_UInt8Ref LPAREN UInt8Ref COMMA
#define SPLIT_UInt32Ref LPAREN UInt32Ref COMMA
#define SPLIT_objectPtr LPAREN objectPtr COMMA
#define SPLIT_StringCharPtr LPAREN StringCharPtr COMMA
#define SPLIT_OutputStringViewPtr LPAREN OutputStringViewPtr COMMA

#define V8_TO_int(info, var) V8_TO_INT32(info, var)
#define V8_TO_bool(info, var) V8_TO_BOOLEAN(info, var)
#define V8_TO_uint32_t(info, var) V8_TO_UINT32(info, var)
#define V8_TO_uint8_t(info, var) V8_TO_UINT32(info, var)
#define V8_TO_float(info, var) V8_TO_FLOAT(info, var)
#define V8_TO_IntRef(info, var) int var
#define V8_TO_FloatRef(info, var) float var
#define V8_TO_BoolRef(info, var) bool var
#define V8_TO_UInt32Ref(info, var) uint32_t var
#define V8_TO_UInt8Ref(info, var) uint8_t var
#define V8_TO_objectPtr(info, var) V8_TO_UINTPTR(info, var)
#define V8_TO_StringCharPtr(info, var) V8_TO_STRING(info, var)
#define V8_TO_OutputStringViewPtr(info, var) \
	CAPIStringView var { 0, nullptr }

#define VAR_TO_PASS_IntRef(a) &a
#define VAR_TO_PASS_FloatRef(a) &a
#define VAR_TO_PASS_BoolRef(a) &a
#define VAR_TO_PASS_UInt32Ref(a) &a
#define VAR_TO_PASS_UInt8Ref(a) &a
#define VAR_TO_PASS_int(a) a
#define VAR_TO_PASS_bool(a) a
#define VAR_TO_PASS_float(a) a
#define VAR_TO_PASS_uint32_t(a) a
#define VAR_TO_PASS_uint8_t(a) a
#define VAR_TO_PASS_objectPtr(a) a
#define VAR_TO_PASS_StringCharPtr(a) a.c_str()
#define VAR_TO_PASS_OutputStringViewPtr(a) &a

#define CAST_TYPE_FOR_RETURN_objectPtr uintptr_t
#define CAST_TYPE_FOR_RETURN_int int
#define CAST_TYPE_FOR_RETURN_bool bool
#define CAST_TYPE_FOR_RETURN_float float
#define CAST_TYPE_FOR_RETURN_uint32_t uint32_t
#define CAST_TYPE_FOR_RETURN_uint8_t uint32_t
#define CAST_TYPE_FOR_RETURN_IntRef *
#define CAST_TYPE_FOR_RETURN_FloatRef *
#define CAST_TYPE_FOR_RETURN_BoolRef *
#define CAST_TYPE_FOR_RETURN_UInt32Ref *
#define CAST_TYPE_FOR_RETURN_UInt8Ref *
#define CAST_TYPE_FOR_RETURN_OutputStringViewPtr(x) Impl::String(x->data, x->len)

#define DECLARE_VARIABLE_NATIVELY_(x, y, idx) CAT2(V8_TO_, x)(info[idx], y)
#define DECLARE_VARIABLE_NATIVELY(idx, A) SPLIT_INDEX(DECLARE_VARIABLE_NATIVELY_, A, idx)

#define CREATE_FUNCTION_CALL_ARG_(x, y) CAT2(VAR_TO_PASS_, x)(y)
#define CREATE_FUNCTION_CALL_ARG(A) EXPAND2(SPLIT(CREATE_FUNCTION_CALL_ARG_, A))

#define CREATE_RETURN_OBJECT_ELEMENT_(x, y) retJson[#y] = CAT2(CAST_TYPE_FOR_RETURN_, x)(y)
#define CREATE_RETURN_OBJECT_ELEMENT(A) EXPAND2(SPLIT(CREATE_RETURN_OBJECT_ELEMENT_, A))

#ifdef _MSC_VER
#define OMP_NODE__NUM_ARGS(...) OMP_NODE__NUM_ARGS_(OMP_NODE__NUM_ARGS_MSVC(__VA_ARGS__))

#define OMP_NODE__NUM_ARGS_MSVC(...) unused, __VA_ARGS__
#define OMP_NODE__NUM_ARGS_(...) EXPAND(OMP_NODE__NUM_ARGS_IMPL(__VA_ARGS__, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define OMP_NODE__NUM_ARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, N, ...) N
#else
#define OMP_NODE__NUM_ARGS(...) OMP_NODE__NUM_ARGS_(__VA_ARGS__)
#define OMP_NODE__NUM_ARGS_(...) OMP_NODE__NUM_ARGS_IMPL(0, ##__VA_ARGS__, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define OMP_NODE__NUM_ARGS_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, N, ...) N
#endif

#define PREPEND_ARGS_TO_DECLARE_VARS_0(index, ...) EMPTY()
#define PREPEND_ARGS_TO_DECLARE_VARS_1(index, a) DECLARE_VARIABLE_NATIVELY(index, a);
#define PREPEND_ARGS_TO_DECLARE_VARS_2(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);              \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_1(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_3(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);              \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_2(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_4(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);              \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_3(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_5(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);              \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_4(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_6(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);              \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_5(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_7(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);              \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_6(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_8(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);              \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_7(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_9(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);              \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_8(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_10(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_9(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_11(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_10(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_12(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_11(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_13(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_12(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_14(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_13(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_15(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_14(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_16(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_15(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_17(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_16(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_18(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_17(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_19(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_18(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_20(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_19(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_21(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_20(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_22(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_21(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_23(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_22(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_24(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_23(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_25(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_24(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_26(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_25(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_27(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_26(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_28(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_27(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_29(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_28(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_30(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_29(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_31(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_30(INC(index), __VA_ARGS__))
#define PREPEND_ARGS_TO_DECLARE_VARS_32(index, a, ...) \
	DECLARE_VARIABLE_NATIVELY(index, a);               \
	EVAL(PREPEND_ARGS_TO_DECLARE_VARS_31(INC(index), __VA_ARGS__))

#define PREPEND_ARGS_IN_FUNCTION_CALL_0() EMPTY()
#define PREPEND_ARGS_IN_FUNCTION_CALL_1(a) CREATE_FUNCTION_CALL_ARG(a),
#define PREPEND_ARGS_IN_FUNCTION_CALL_2(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_1(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_3(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_2(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_4(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_3(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_5(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_4(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_6(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_5(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_7(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_6(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_8(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_7(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_9(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_8(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_10(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_9(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_11(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_10(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_12(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_11(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_13(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_12(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_14(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_13(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_15(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_14(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_16(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_15(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_17(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_16(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_18(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_17(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_19(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_18(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_20(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_19(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_21(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_20(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_22(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_21(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_23(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_22(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_24(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_23(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_25(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_24(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_26(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_25(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_27(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_26(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_28(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_27(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_29(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_28(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_30(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_29(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_31(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_30(__VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_32(a, ...) CREATE_FUNCTION_CALL_ARG(a), EVAL(PREPEND_ARGS_IN_FUNCTION_CALL_31(__VA_ARGS__))

#define GENERATE_RETURN_VAR_()
#define GENERATE_RETURN_VAR_0() EMPTY()
#define GENERATE_RETURN_VAR_1(a) CREATE_RETURN_OBJECT_ELEMENT(a);
#define GENERATE_RETURN_VAR_2(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);  \
	EVAL(GENERATE_RETURN_VAR_1(__VA_ARGS__))
#define GENERATE_RETURN_VAR_3(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);  \
	EVAL(GENERATE_RETURN_VAR_2(__VA_ARGS__))
#define GENERATE_RETURN_VAR_4(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);  \
	EVAL(GENERATE_RETURN_VAR_3(__VA_ARGS__))
#define GENERATE_RETURN_VAR_5(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);  \
	EVAL(GENERATE_RETURN_VAR_4(__VA_ARGS__))
#define GENERATE_RETURN_VAR_6(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);  \
	EVAL(GENERATE_RETURN_VAR_5(__VA_ARGS__))
#define GENERATE_RETURN_VAR_7(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);  \
	EVAL(GENERATE_RETURN_VAR_6(__VA_ARGS__))
#define GENERATE_RETURN_VAR_8(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);  \
	EVAL(GENERATE_RETURN_VAR_7(__VA_ARGS__))
#define GENERATE_RETURN_VAR_9(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);  \
	EVAL(GENERATE_RETURN_VAR_8(__VA_ARGS__))
#define GENERATE_RETURN_VAR_10(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_9(__VA_ARGS__))
#define GENERATE_RETURN_VAR_11(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_10(__VA_ARGS__))
#define GENERATE_RETURN_VAR_12(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_11(__VA_ARGS__))
#define GENERATE_RETURN_VAR_13(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_12(__VA_ARGS__))
#define GENERATE_RETURN_VAR_14(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_13(__VA_ARGS__))
#define GENERATE_RETURN_VAR_15(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_14(__VA_ARGS__))
#define GENERATE_RETURN_VAR_16(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_15(__VA_ARGS__))
#define GENERATE_RETURN_VAR_17(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_16(__VA_ARGS__))
#define GENERATE_RETURN_VAR_18(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_17(__VA_ARGS__))
#define GENERATE_RETURN_VAR_19(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_18(__VA_ARGS__))
#define GENERATE_RETURN_VAR_20(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_19(__VA_ARGS__))
#define GENERATE_RETURN_VAR_21(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_20(__VA_ARGS__))
#define GENERATE_RETURN_VAR_22(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_21(__VA_ARGS__))
#define GENERATE_RETURN_VAR_23(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_22(__VA_ARGS__))
#define GENERATE_RETURN_VAR_24(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_23(__VA_ARGS__))
#define GENERATE_RETURN_VAR_25(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_24(__VA_ARGS__))
#define GENERATE_RETURN_VAR_26(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_25(__VA_ARGS__))
#define GENERATE_RETURN_VAR_27(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_26(__VA_ARGS__))
#define GENERATE_RETURN_VAR_28(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_27(__VA_ARGS__))
#define GENERATE_RETURN_VAR_29(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_28(__VA_ARGS__))
#define GENERATE_RETURN_VAR_30(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_29(__VA_ARGS__))
#define GENERATE_RETURN_VAR_31(a, ...) \
	CREATE_RETURN_OBJECT_ELEMENT(a);   \
	EVAL(GENERATE_RETURN_VAR_30(__VA_ARGS__))

#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_0() EMPTY()
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_1(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_2(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_3(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_4(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_5(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_6(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_7(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_8(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_9(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_10(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_11(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_12(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_13(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_14(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_15(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_16(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_17(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_18(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_19(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_20(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_21(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_22(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_23(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_24(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_25(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_26(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_27(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_28(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_29(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_30(...) __VA_ARGS__,
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_31(...) __VA_ARGS__,

#define PREPEND_ARGS_TO_DECLARE_VARS_IMPL(...) EVAL(CAT2(PREPEND_ARGS_TO_DECLARE_VARS_, OMP_NODE__NUM_ARGS(__VA_ARGS__))(0, __VA_ARGS__))
#define PREPEND_ARGS_IN_FUNCTION_CALL_IMPL(...) EVAL(CAT2(PREPEND_ARGS_IN_FUNCTION_CALL_, OMP_NODE__NUM_ARGS(__VA_ARGS__))(__VA_ARGS__))
#define GENERATE_RETURN_VAR_IMPL(...) EVAL(CAT2(GENERATE_RETURN_VAR_, OMP_NODE__NUM_ARGS(__VA_ARGS__))(__VA_ARGS__))

#define GENERATE_PARAMS_TO_DECLARE_VARS(...) PREPEND_ARGS_TO_DECLARE_VARS_IMPL(__VA_ARGS__)
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG(...) CAT2(GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG_, OMP_NODE__NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_CALL(...) PREPEND_ARGS_IN_FUNCTION_CALL_IMPL(__VA_ARGS__)

// Increment macros
#define INC_0 1
#define INC_1 2
#define INC_2 3
#define INC_3 4
#define INC_4 5
#define INC_5 6
#define INC_6 7
#define INC_7 8
#define INC_8 9
#define INC_9 10
#define INC_10 11
#define INC_11 12
#define INC_12 13
#define INC_13 14
#define INC_14 15
#define INC_15 16
#define INC_16 17
#define INC_17 18
#define INC_18 19
#define INC_19 20
#define INC_20 21
#define INC_21 22
#define INC_22 23
#define INC_23 24
#define INC_24 25
#define INC_25 26
#define INC_26 27
#define INC_27 28
#define INC_28 29
#define INC_29 30
#define INC_30 31
#define INC_31 32
#define INC_32 33

#define INC(X) INC_##X

// name: name for IPC event sent from clients (other languages)
// params: params in nlohmann::json object
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

#define API_RETURN(...)                   \
	nlohmann::json retJson;               \
	GENERATE_RETURN_VAR_IMPL(__VA_ARGS__) \
	return retJson
