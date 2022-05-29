#include <utility>

#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "checkpoint_event_dispatcher_wrapper.hpp"
#include "../../converter/entity.hpp"

WRAP_BASIC(ICheckpointEventDispatcher)
WRAP_HANDLER_BASIC(PlayerCheckpointEventHandler, NodeJSCheckpointEventHandler)

WRAP_HANDLER(NodeJSCheckpointEventHandler, void, onPlayerEnterCheckpoint, 1, {
    args[0] = EntityToJS<IPlayer>(player, context);
}, return, return, IPlayer &player)

WRAP_HANDLER(NodeJSCheckpointEventHandler, void, onPlayerLeaveCheckpoint, 1, {
    args[0] = EntityToJS<IPlayer>(player, context);
}, return, return, IPlayer &player)

WRAP_HANDLER(NodeJSCheckpointEventHandler, void, onPlayerEnterRaceCheckpoint, 1, {
    args[0] = EntityToJS<IPlayer>(player, context);
}, return, return, IPlayer &player)

WRAP_HANDLER(NodeJSCheckpointEventHandler, void, onPlayerLeaveRaceCheckpoint, 1, {
    args[0] = EntityToJS<IPlayer>(player, context);
}, return, return, IPlayer &player)

WRAP_BASIC_CODE(ICheckpointEventDispatcher, addEventHandler, WRAP_ADD_EVENT_HANDLER(NodeJSCheckpointEventHandler))

WRAP_BASIC_CODE(ICheckpointEventDispatcher, hasEventHandler, WRAP_HAS_EVENT_HANDLER(NodeJSCheckpointEventHandler))

WRAP_BASIC_CODE(ICheckpointEventDispatcher, removeEventHandler, WRAP_REMOVE_EVENT_HANDLER(NodeJSCheckpointEventHandler))

WRAP_BASIC_CALL_RETURN(ICheckpointEventDispatcher, count, (size_t, UIntToJS))

EventDispatcherHandleStorage *WrapCheckpointEventDispatcher(ICheckpointEventDispatcher *dispatcher,
                                                            v8::Local<v8::Context> context) {
    v8::HandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(dispatcher, context, WRAPPED_METHODS(ICheckpointEventDispatcher));

    return new EventDispatcherHandleStorage(context->GetIsolate(), dispatcherHandle);
}