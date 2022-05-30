#include <utility>

#include "menu_wrapper.hpp"
#include "../../converter/types.hpp"
#include "../../converter/entity.hpp"
#include "menu_event_dispatcher_wrapper.hpp"

WRAP_BASIC(IMenuEventDispatcher)
WRAP_HANDLER_BASIC(MenuEventHandler, NodeJSMenuEventHandler)

WRAP_HANDLER(NodeJSMenuEventHandler, void, onPlayerSelectedMenuRow, 2, {
    args[0] = EntityToJS<IPlayer>(player, context);
    args[1] = UIntToJS<MenuRow>(row, context);
}, return, return, IPlayer &player, MenuRow row)

WRAP_HANDLER(NodeJSMenuEventHandler, void, onPlayerExitedMenu, 1, {
    args[0] = EntityToJS<IPlayer>(player, context);
}, return, return, IPlayer &player)

WRAP_BASIC_CODE(IMenuEventDispatcher, addEventHandler, WRAP_ADD_EVENT_HANDLER(NodeJSMenuEventHandler))

WRAP_BASIC_CODE(IMenuEventDispatcher, hasEventHandler, WRAP_HAS_EVENT_HANDLER(NodeJSMenuEventHandler))

WRAP_BASIC_CODE(IMenuEventDispatcher, removeEventHandler, WRAP_REMOVE_EVENT_HANDLER(NodeJSMenuEventHandler))

WRAP_BASIC_CALL_RETURN(IMenuEventDispatcher, count, (size_t, UIntToJS))

EventDispatcherHandleStorage *WrapMenuEventDispatcher(IEventDispatcher<MenuEventHandler> *dispatcher,
                                                      v8::Local<v8::Context> context) {
    v8::HandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(dispatcher, context, WRAPPED_METHODS(IMenuEventDispatcher));

    return new EventDispatcherHandleStorage(context->GetIsolate(), dispatcherHandle);
}