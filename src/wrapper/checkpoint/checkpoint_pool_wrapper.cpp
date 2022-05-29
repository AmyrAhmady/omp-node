#include "../../logger.hpp"
#include "checkpoint_pool_wrapper.hpp"
#include "checkpoint_event_dispatcher_wrapper.hpp"
#include "../entry_handler.hpp"

WRAP_BASIC(ICheckpointsComponent)

WRAP_LOCAL_EXT_HANDLE_STORAGE_GET(ICheckpointsComponent, getEventDispatcher, EventDispatcherHandleStorage)

void WrapCheckpointPool(ICheckpointsComponent *checkpointPool, v8::Local<v8::Context> context) {
    auto checkpointPoolHandle = InterfaceToObject(checkpointPool, context, WRAPPED_METHODS(ICheckpointsComponent));
    checkpointPool->addExtension(new IHandleStorage(context->GetIsolate(), checkpointPoolHandle), true);

    auto eventDispatcherHandleStorage = WrapCheckpointEventDispatcher(&checkpointPool->getEventDispatcher(), context);
    checkpointPool->addExtension(eventDispatcherHandleStorage, true);
}
