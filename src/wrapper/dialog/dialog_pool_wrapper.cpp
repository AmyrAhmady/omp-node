#include "../../logger.hpp"
#include "dialog_pool_wrapper.hpp"
#include "dialog_event_dispatcher_wrapper.hpp"
#include "../entry_handler.hpp"

WRAP_BASIC(IDialogsComponent)

WRAP_LOCAL_EXT_HANDLE_STORAGE_GET(IDialogsComponent, getEventDispatcher, EventDispatcherHandleStorage)

void WrapDialogPool(IDialogsComponent *dialogPool, v8::Local<v8::Context> context) {
    auto dialogPoolHandle = InterfaceToObject(dialogPool, context, WRAPPED_METHODS(IDialogsComponent));
    dialogPool->addExtension(new IHandleStorage(context->GetIsolate(), dialogPoolHandle), true);

    auto eventDispatcherHandleStorage = WrapDialogEventDispatcher(&dialogPool->getEventDispatcher(), context);
    dialogPool->addExtension(eventDispatcherHandleStorage, true);
}