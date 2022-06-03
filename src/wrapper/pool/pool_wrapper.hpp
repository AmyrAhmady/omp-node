#pragma once
#include "pool_event_dispatcher_wrapper.hpp"

#define WRAP_POOL_METHODS_WITHOUT_DISPATCHER(Type) \
    WRAP_BASIC_CALL(Type, release, (int, JSToInt<int>, index)) \
    WRAP_BASIC_CALL(Type, lock, (int, JSToInt<int>, index)) \
    WRAP_BASIC_CALL(Type, unlock, (int, JSToInt<int>, index)) \
    WRAP_BASIC_CALL_RETURN(Type, count, (size_t, IntToJS<size_t>)) \
    WRAP_BASIC_CODE(Type, entries, { \
        auto external = GetContextExternalPointer<Type>(info); \
        if (external == nullptr) { \
            return; \
        } \
        v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), external->count()); \
        if (array.IsEmpty()) { \
            return; \
        } \
        int index = 0; \
        for (auto entry : *external) { \
            array->Set(context, index++, EntityToJS(entry, context)).Check(); \
        } \
        info.GetReturnValue().Set(array); \
    })

#define WRAP_POOL_METHODS(Type, EntityType) \
    WRAP_POOL_METHODS_WITHOUT_DISPATCHER(Type) \
    WRAP_POOL_EVENT_DISPATCHER(Type, EntityType) \
    WRAP_LOCAL_EXT_HANDLE_STORAGE_GET(Type, getPoolEventDispatcher, PoolEventDispatcherHandleStorage)
