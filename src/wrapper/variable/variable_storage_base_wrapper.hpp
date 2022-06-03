#pragma once

#define WRAP_VARIABLE_STORAGE_BASE_METHODS(Type) \
    WRAP_BASIC_CALL(Type, setString, (Impl::String, JSToString, key), (Impl::String, JSToString, value)) \
    WRAP_BASIC_CALL_RETURN(Type, \
                           getString, \
                           (const StringView, TO_JS_FN(StringView)), \
                           (Impl::String, JSToString, key)) \
    WRAP_BASIC_CALL(Type, setInt, (Impl::String, JSToString, key), (int, JSToInt<int>, value)) \
    WRAP_BASIC_CALL_RETURN(Type, getInt, (int, IntToJS<int>), (Impl::String, JSToString, key)) \
    WRAP_BASIC_CALL(Type, setFloat, (Impl::String, JSToString, key), (float, JSToFloat, value)) \
    WRAP_BASIC_CALL_RETURN(Type, getFloat, (float, FloatToJS), (Impl::String, JSToString, key)) \
    WRAP_BASIC_CALL_RETURN(Type, \
                           getType, \
                           (VariableType, EnumToJS<VariableType>), \
                           (Impl::String, JSToString, key)) \
    WRAP_BASIC_CALL_RETURN(Type, erase, (bool, BoolToJS), (Impl::String, JSToString, key)) \
    WRAP_BASIC_CODE(Type, getKeyAtIndex, { \
        auto external = GetContextExternalPointer<Type>(info); \
        if (external == nullptr) { \
            return; \
        } \
        v8::TryCatch tryCatch(isolate); \
        int index = JSToInt<int>(info[0], context); \
        if (tryCatch.HasCaught()) { \
            tryCatch.ReThrow(); \
            return; \
        } \
        StringView key; \
        bool value = external->getKeyAtIndex(index, key); \
        if (value) { \
            info.GetReturnValue().Set(StringViewToJS(key, context)); \
        } else { \
            info.GetReturnValue().Set(v8::Null(isolate)); \
        } \
    }) \
    WRAP_BASIC_CALL_RETURN(Type, size, (int, IntToJS<int>))