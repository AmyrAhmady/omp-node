#pragma once
#include "pool_event_dispatcher_wrapper.hpp"

#define WRAP_POOL_METHODS(Type, EntityType) \
    WRAP_BASIC_CALL(Type, release, (int, JSToInt<int>, index)) \
    WRAP_BASIC_CALL(Type, lock, (int, JSToInt<int>, index)) \
    WRAP_BASIC_CALL(Type, unlock, (int, JSToInt<int>, index)) \
    WRAP_BASIC_CALL_RETURN(Type, count, (size_t, IntToJS<size_t>)) \
    WRAP_POOL_EVENT_DISPATCHER(Type, EntityType) \
    WRAP_BASIC_CODE(Type, getPoolEventDispatcher, { \
        ENTER_FUNCTION_CALLBACK(info) \
        auto pool = GetContextExternalPointer<Type>(info); \
        auto dispatcher = &pool->getPoolEventDispatcher(); \
        auto dispatcherHandle = WRAPPED_POOL_EVENT_DISPATCHER(EntityType)(dispatcher, context); \
        info.GetReturnValue().Set(dispatcherHandle); \
    })
