#include <utility>

#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"
#include "../../converter/gangzone.hpp"
#include "checkpoint_event_dispatcher_wrapper.hpp"

WRAP_BASIC(ICheckpointEventDispatcher)
WRAP_HANDLER_BASIC(PlayerCheckpointEventHandler, NodeJSCheckpointEventHandler)

WRAP_HANDLER(NodeJSCheckpointEventHandler, void, onPlayerEnterCheckpoint, 1, {
    args[0] = IPlayerToJS(player, context);
}, return, return, IPlayer &player)

WRAP_HANDLER(NodeJSCheckpointEventHandler, void, onPlayerLeaveCheckpoint, 1, {
    args[0] = IPlayerToJS(player, context);
}, return, return, IPlayer &player)

WRAP_HANDLER(NodeJSCheckpointEventHandler, void, onPlayerEnterRaceCheckpoint, 1, {
    args[0] = IPlayerToJS(player, context);
}, return, return, IPlayer &player)

WRAP_HANDLER(NodeJSCheckpointEventHandler, void, onPlayerLeaveRaceCheckpoint, 1, {
    args[0] = IPlayerToJS(player, context);
}, return, return, IPlayer &player)

WRAP_BASIC_CODE(ICheckpointEventDispatcher, addEventHandler, WRAP_ADD_EVENT_HANDLER(NodeJSCheckpointEventHandler))

WRAP_BASIC_CODE(ICheckpointEventDispatcher, hasEventHandler, WRAP_HAS_EVENT_HANDLER(NodeJSCheckpointEventHandler))

WRAP_BASIC_CODE(ICheckpointEventDispatcher, removeEventHandler, WRAP_REMOVE_EVENT_HANDLER(NodeJSCheckpointEventHandler))

WRAP_BASIC_CALL_RETURN(ICheckpointEventDispatcher, count, (size_t, UIntToJS))

v8::Local<v8::Value> WrapCheckpointEventDispatcher(ICheckpointEventDispatcher *dispatcher,
                                                 v8::Local<v8::Context> context) {

    v8::EscapableHandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(dispatcher, context, WRAPPED_METHODS(ICheckpointEventDispatcher));

    return hs.Escape(dispatcherHandle);
}