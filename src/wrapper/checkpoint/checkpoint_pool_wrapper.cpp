#include "../../logger.hpp"
#include "checkpoint_pool_wrapper.hpp"
#include "checkpoint_event_dispatcher_wrapper.hpp"
#include "../entry_handler.hpp"

WRAP_BASIC(ICheckpointsComponent)

WRAP_BASIC_CODE(ICheckpointsComponent, getEventDispatcher, {
    ENTER_FUNCTION_CALLBACK(info)
    auto pool = GetContextExternalPointer<ICheckpointsComponent>(info);
    auto dispatcher = &pool->getEventDispatcher();
    auto dispatcherHandle = WrapCheckpointEventDispatcher(dispatcher, context);
    info.GetReturnValue().Set(dispatcherHandle);
})

void WrapCheckpointPool(ICheckpointsComponent *checkpointPool, v8::Local<v8::Context> context) {
    auto checkpointPoolHandle = InterfaceToObject(checkpointPool, context, WRAPPED_METHODS(ICheckpointsComponent));

    checkpointPool->addExtension(new IHandleStorage(context->GetIsolate(), checkpointPoolHandle), true);
}