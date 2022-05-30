#include <utility>

#include "textdraw_wrapper.hpp"
#include "player_textdraw_wrapper.hpp"
#include "../../converter/types.hpp"
#include "../../converter/entity.hpp"
#include "textdraw_event_dispatcher_wrapper.hpp"

WRAP_BASIC(ITextDrawEventDispatcher)
WRAP_HANDLER_BASIC(TextDrawEventHandler, NodeJSTextDrawEventHandler)

WRAP_HANDLER(NodeJSTextDrawEventHandler, void, onPlayerClickTextDraw, 2, {
    args[0] = EntityToJS<IPlayer>(player, context);
    args[1] = EntityToJS<ITextDraw>(td, context);
}, return, return, IPlayer& player, ITextDraw& td)

WRAP_HANDLER(NodeJSTextDrawEventHandler, void, onPlayerClickPlayerTextDraw, 2, {
    args[0] = EntityToJS<IPlayer>(player, context);
    args[1] = EntityToJS<IPlayerTextDraw>(td, context);
}, return, return, IPlayer& player, IPlayerTextDraw& td)

WRAP_HANDLER(NodeJSTextDrawEventHandler, bool, onPlayerCancelTextDrawSelection, 1, {
    args[0] = EntityToJS<IPlayer>(player, context);
}, return JSToBool(cbReturnedValue, context), return false, IPlayer& player)

WRAP_HANDLER(NodeJSTextDrawEventHandler, bool, onPlayerCancelPlayerTextDrawSelection, 1, {
    args[0] = EntityToJS<IPlayer>(player, context);
}, return JSToBool(cbReturnedValue, context), return false, IPlayer& player)

WRAP_BASIC_CODE(ITextDrawEventDispatcher, addEventHandler, WRAP_ADD_EVENT_HANDLER(NodeJSTextDrawEventHandler))

WRAP_BASIC_CODE(ITextDrawEventDispatcher, hasEventHandler, WRAP_HAS_EVENT_HANDLER(NodeJSTextDrawEventHandler))

WRAP_BASIC_CODE(ITextDrawEventDispatcher, removeEventHandler, WRAP_REMOVE_EVENT_HANDLER(NodeJSTextDrawEventHandler))

WRAP_BASIC_CALL_RETURN(ITextDrawEventDispatcher, count, (size_t, UIntToJS))

EventDispatcherHandleStorage *WrapTextDrawEventDispatcher(IEventDispatcher<TextDrawEventHandler> *dispatcher,
                                                        v8::Local<v8::Context> context) {
    v8::HandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(dispatcher, context, WRAPPED_METHODS(ITextDrawEventDispatcher));

    return new EventDispatcherHandleStorage(context->GetIsolate(), dispatcherHandle);
}