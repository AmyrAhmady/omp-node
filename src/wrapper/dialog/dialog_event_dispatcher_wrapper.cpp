#include <utility>
#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "dialog_event_dispatcher_wrapper.hpp"
#include "../../converter/entity.hpp"

WRAP_BASIC(IDialogEventDispatcher)
WRAP_HANDLER_BASIC(PlayerDialogEventHandler, NodeJSDialogEventHandler)

WRAP_HANDLER(NodeJSDialogEventHandler, void, onDialogResponse, 5, {
    args[0] = EntityToJS<IPlayer>(player, context);
    args[1] = IntToJS(dialogId, context);
    args[2] = EnumToJS(response, context);
    args[3] = IntToJS(listItem, context);
    args[4] = StringViewToJS(inputText, context);
}, return, return, IPlayer &player, int dialogId, DialogResponse response, int listItem, StringView inputText)

WRAP_BASIC_CODE(IDialogEventDispatcher, addEventHandler, WRAP_ADD_EVENT_HANDLER(NodeJSDialogEventHandler))
WRAP_BASIC_CODE(IDialogEventDispatcher, hasEventHandler, WRAP_HAS_EVENT_HANDLER(NodeJSDialogEventHandler))
WRAP_BASIC_CODE(IDialogEventDispatcher, removeEventHandler, WRAP_REMOVE_EVENT_HANDLER(NodeJSDialogEventHandler))

WRAP_BASIC_CALL_RETURN(IDialogEventDispatcher, count, (size_t, UIntToJS))

EventDispatcherHandleStorage *WrapDialogEventDispatcher(IEventDispatcher<PlayerDialogEventHandler> *dispatcher,
                                                        v8::Local<v8::Context> context) {
    v8::HandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(dispatcher, context, WRAPPED_METHODS(IDialogEventDispatcher));

    return new EventDispatcherHandleStorage(context->GetIsolate(), dispatcherHandle);
}