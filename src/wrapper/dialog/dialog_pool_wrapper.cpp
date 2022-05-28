#include "../../logger.hpp"
#include "dialog_pool_wrapper.hpp"
#include "dialog_event_dispatcher_wrapper.hpp"
#include "../entry_handler.hpp"

WRAP_BASIC(IDialogsComponent)

WRAP_BASIC_CODE(IDialogsComponent, getEventDispatcher, {
    ENTER_FUNCTION_CALLBACK(info)
    auto pool = GetContextExternalPointer<IDialogsComponent>(info);
    auto dispatcher = &pool->getEventDispatcher();
    auto dispatcherHandle = WrapDialogEventDispatcher(dispatcher, context);
    info.GetReturnValue().Set(dispatcherHandle);
})

void WrapDialogPool(IDialogsComponent *dialogPool, v8::Local<v8::Context> context) {
    auto dialogPoolHandle = InterfaceToObject(dialogPool, context, WRAPPED_METHODS(IDialogsComponent));

    dialogPool->addExtension(new IHandleStorage(context->GetIsolate(), dialogPoolHandle), true);
}