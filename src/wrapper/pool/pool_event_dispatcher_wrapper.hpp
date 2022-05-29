#define WRAP_POOL_EVENT_DISPATCHER(PoolType, EntityType) \
    typedef PoolEventHandler<EntityType> PoolType##EventHandler; \
    typedef IEventDispatcher<PoolEventHandler<EntityType>> EntityType##PoolEventDispatcher; \
    WRAP_BASIC(EntityType##PoolEventDispatcher) \
    WRAP_HANDLER_BASIC(PoolType##EventHandler, NodeJS##PoolType##EventHandler) \
    WRAP_HANDLER(NodeJS##PoolType##EventHandler, void, onPoolEntryCreated, 1, { \
        args[0] = GetHandleStorageExtension(&entity)->get(); \
    }, return, return, EntityType &entity) \
    WRAP_HANDLER(NodeJS##PoolType##EventHandler, void, onPoolEntryDestroyed, 1, { \
        args[0] = GetHandleStorageExtension(&entity)->get(); \
    }, return, return, EntityType &entity) \
    WRAP_BASIC_CODE(EntityType##PoolEventDispatcher, addEventHandler, WRAP_ADD_EVENT_HANDLER(NodeJS##PoolType##EventHandler)) \
    WRAP_BASIC_CODE(EntityType##PoolEventDispatcher, hasEventHandler, WRAP_HAS_EVENT_HANDLER(NodeJS##PoolType##EventHandler)) \
    WRAP_BASIC_CODE(EntityType##PoolEventDispatcher, removeEventHandler, WRAP_REMOVE_EVENT_HANDLER(NodeJS##PoolType##EventHandler)) \
    WRAP_BASIC_CALL_RETURN(EntityType##PoolEventDispatcher, count, (size_t, UIntToJS)) \
    PoolEventDispatcherHandleStorage* Wrap##EntityType##PoolEventDispatcher(EntityType##PoolEventDispatcher *dispatcher, \
                                                        v8::Local<v8::Context> context) __attribute__((warn_unused_result)); \
    PoolEventDispatcherHandleStorage* Wrap##EntityType##PoolEventDispatcher(EntityType##PoolEventDispatcher *dispatcher, \
                                                        v8::Local<v8::Context> context) { \
        v8::HandleScope hs(context->GetIsolate()); \
        auto dispatcherHandle = InterfaceToObject(dispatcher, context, WRAPPED_METHODS(EntityType##PoolEventDispatcher));     \
        return new PoolEventDispatcherHandleStorage(context->GetIsolate(), dispatcherHandle);\
    }

#define WRAPPED_POOL_EVENT_DISPATCHER(EntityType) Wrap##EntityType##PoolEventDispatcher