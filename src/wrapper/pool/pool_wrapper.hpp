#pragma once


#define WRAP_POOL_METHODS(Type, WrapPoolEventDispatcher) \
    WRAP_BASIC_CALL(Type, release, (int, JSToInt<int>, index)) \
    WRAP_BASIC_CALL(Type, lock, (int, JSToInt<int>, index)) \
    WRAP_BASIC_CALL(Type, unlock, (int, JSToInt<int>, index)) \
    WRAP_BASIC_CALL_RETURN(Type, count, (size_t, IntToJS<size_t>)) \
    WRAP_BASIC_CODE(Type, getPoolEventDispatcher, { \
        ENTER_FUNCTION_CALLBACK(info) \
        auto pool = GetContextExternalPointer<Type>(info); \
        auto dispatcher = &pool->getPoolEventDispatcher(); \
        auto dispatcherHandle = WrapPoolEventDispatcher(dispatcher, context); \
        info.GetReturnValue().Set(dispatcherHandle); \
    })
