#include <utility>

#include "player_wrapper.hpp"
#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "player_pool_event_dispatcher_wrapper.hpp"

WRAP_BASIC(IPlayerPoolEventDispatcher)
WRAP_HANDLER_BASIC(PlayerPoolEventHandler, NodeJSPlayerPoolEventHandler)

WRAP_HANDLER(NodeJSPlayerPoolEventHandler, void, onPoolEntryCreated, 1, {
    args[0] = GetHandleStorageExtension(&player)->get();
}, return, IPlayer &player)

WRAP_HANDLER(NodeJSPlayerPoolEventHandler, void, onPoolEntryDestroyed, 1, {
    args[0] = GetHandleStorageExtension(&player)->get();
}, return, IPlayer &player)

WRAP_BASIC_CODE(IPlayerPoolEventDispatcher, addEventHandler, WRAP_ADD_EVENT_HANDLER(NodeJSPlayerPoolEventHandler))

WRAP_BASIC_CODE(IPlayerPoolEventDispatcher, hasEventHandler, WRAP_HAS_EVENT_HANDLER(NodeJSPlayerPoolEventHandler))

WRAP_BASIC_CODE(IPlayerPoolEventDispatcher, removeEventHandler, WRAP_REMOVE_EVENT_HANDLER(NodeJSPlayerPoolEventHandler))

WRAP_BASIC_CALL_RETURN(IPlayerPoolEventDispatcher, count, (size_t, UIntToJS))

v8::Local<v8::Value> WrapPlayerPoolEventDispatcher(IEventDispatcher<PlayerPoolEventHandler> *dispatcher,
                                                   v8::Local<v8::Context> context) {

    v8::EscapableHandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(dispatcher, context, WRAPPED_METHODS(IPlayerPoolEventDispatcher));

    return hs.Escape(dispatcherHandle);
}