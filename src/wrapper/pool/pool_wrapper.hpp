#pragma once
#include "pool_event_dispatcher_wrapper.hpp"

#define WRAP_POOL_METHODS(Type, EntityType) \
    WRAP_BASIC_CALL(Type, release, (int, JSToInt<int>, index)) \
    WRAP_BASIC_CALL(Type, lock, (int, JSToInt<int>, index)) \
    WRAP_BASIC_CALL(Type, unlock, (int, JSToInt<int>, index)) \
    WRAP_BASIC_CALL_RETURN(Type, count, (size_t, IntToJS<size_t>)) \
    WRAP_POOL_EVENT_DISPATCHER(Type, EntityType) \
    WRAP_LOCAL_EXT_HANDLE_STORAGE_GET(Type, getPoolEventDispatcher, PoolEventDispatcherHandleStorage)
