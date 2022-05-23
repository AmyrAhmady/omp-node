#include "player_wrapper.hpp"
#include "player_event_dispatcher_wrapper.hpp"
#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/player.hpp"
#include "../../converter/types.hpp"
#include "../entry_handler.hpp"

WRAP_BASIC(IPlayerPool)

WRAP_BASIC_CALL_RETURN(IPlayerPool, entries, FlatPtrHashSetIPlayerToJS)
WRAP_BASIC_CALL_RETURN(IPlayerPool, players, FlatPtrHashSetIPlayerToJS)
WRAP_BASIC_CALL_RETURN(IPlayerPool, bots, FlatPtrHashSetIPlayerToJS)
WRAP_BASIC_CODE(IPlayerPool, getEventDispatcher, {
    ENTER_FUNCTION_CALLBACK(info)
    auto playerPool = GetContextExternalPointer<IPlayerPool>(info);
    auto dispatcher = &playerPool->getEventDispatcher();
    auto dispatcherHandle = WrapPlayerEventDispatcher(dispatcher, context);
    info.GetReturnValue().Set(dispatcherHandle);
})
WRAP_BASIC_CALL(IPlayerPool, sendClientMessageToAll, JSToColour(info[0], context), JSToString(info[1], context))

NodeJSEntryHandler<IPlayer> *handler;

void WrapPlayerPool(IPlayerPool *playerPool, v8::Local<v8::Context> context) {
    handler = new NodeJSEntryHandler<IPlayer>(context, WrapPlayer); // todo: store somewhere to delete later

    playerPool->getPoolEventDispatcher().addEventHandler(handler);

    auto playerPoolHandle = InterfaceToObject(playerPool, context, WRAPPED_METHODS(IPlayerPool));

    playerPool->addExtension(new IHandleStorage(context->GetIsolate(), playerPoolHandle), true);
}