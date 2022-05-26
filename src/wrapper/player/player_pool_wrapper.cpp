#include "player_wrapper.hpp"
#include "player_event_dispatcher_wrapper.hpp"
#include "player_update_event_dispatcher_wrapper.hpp"
#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/player.hpp"
#include "../../converter/types.hpp"
#include "../entry_handler.hpp"

WRAP_BASIC(IPlayerPool)

WRAP_BASIC_CALL_RETURN(IPlayerPool, entries, (FlatPtrHashSetIPlayer, TO_JS_FN(FlatPtrHashSetIPlayer)))
WRAP_BASIC_CALL_RETURN(IPlayerPool, players, (FlatPtrHashSetIPlayer, TO_JS_FN(FlatPtrHashSetIPlayer)))
WRAP_BASIC_CALL_RETURN(IPlayerPool, bots, (FlatPtrHashSetIPlayer, TO_JS_FN(FlatPtrHashSetIPlayer)))
WRAP_BASIC_CALL_RETURN(IPlayerPool, isNameTaken, (bool, BoolToJS), (Impl::String, JSToString, name), (const IPlayer*, FROM_JS_FN(IPlayer), skip))
WRAP_BASIC_CALL(IPlayerPool, sendClientMessageToAll, (const Colour&, FROM_JS_FN(Colour), colour), (Impl::String, JSToString, message))
WRAP_BASIC_CALL(IPlayerPool, sendChatMessageToAll, (IPlayer&, FROM_JS_FN(IPlayerRef), from), (Impl::String, JSToString, message))
WRAP_BASIC_CALL(IPlayerPool, sendGameTextToAll, (Impl::String, JSToString, message), (Milliseconds, FROM_JS_FN(Milliseconds), time), (int, JSToInt, style))
WRAP_BASIC_CALL(IPlayerPool, sendDeathMessageToAll, (IPlayer*, FROM_JS_FN(IPlayer), killer), (IPlayer&, FROM_JS_FN(IPlayerRef), killee), (int, JSToInt, weapon))
WRAP_BASIC_CALL(IPlayerPool, sendEmptyDeathMessageToAll)
WRAP_BASIC_CALL(IPlayerPool, createExplosionForAll, (Vector3, JSToVector<Vector3>, vec), (int, JSToInt, type), (float, JSToFloat, radius))
//WRAP_BASIC_CALL_RETURN(IPlayerPool, requestPlayer, (Pair<NewConnectionResult, IPlayer*>, TO_JS_FN(Pair<NewConnectionResult, IPlayer*>)), (const PeerNetworkData&, FROM_JS_FN(PeerNetworkData), netData), (const PeerRequestParams&, FROM_JS_FN(PeerRequestParams), params))
//WRAP_BASIC_CALL(IPlayerPool, broadcastRPC, (int, JSToInt, id), (Span<uint8_t>, FROM_JS_FN(Span<uint8_t>), data), (int, JSToInt, channel), (const IPlayer*, FROM_JS_FN(IPlayer), skipFrom, nullptr))
WRAP_BASIC_CALL_RETURN(IPlayerPool, isNameValid, (bool, BoolToJS), (Impl::String, JSToString, name))
WRAP_BASIC_CALL(IPlayerPool, allowNickNameCharacter, (char, JSToInt<char>, character), (bool, JSToBool, allow))
WRAP_BASIC_CALL_RETURN(IPlayerPool, isNickNameCharacterAllowed, (bool, BoolToJS), (char, JSToInt<char>, character))

WRAP_BASIC_CODE(IPlayerPool, getEventDispatcher, {
    ENTER_FUNCTION_CALLBACK(info)
    auto playerPool = GetContextExternalPointer<IPlayerPool>(info);
    auto dispatcher = &playerPool->getEventDispatcher();
    auto dispatcherHandle = WrapPlayerEventDispatcher(dispatcher, context);
    info.GetReturnValue().Set(dispatcherHandle);
})
WRAP_BASIC_CODE(IPlayerPool, getPlayerUpdateDispatcher, {
    ENTER_FUNCTION_CALLBACK(info)
    auto playerPool = GetContextExternalPointer<IPlayerPool>(info);
    auto dispatcher = &playerPool->getPlayerUpdateDispatcher();
    auto dispatcherHandle = WrapPlayerUpdateEventDispatcher(dispatcher, context);
    info.GetReturnValue().Set(dispatcherHandle);
})

NodeJSEntryHandler<IPlayer> *handler;

void WrapPlayerPool(IPlayerPool *playerPool, v8::Local<v8::Context> context) {
    handler = new NodeJSEntryHandler<IPlayer>(context, WrapPlayer); // todo: store somewhere to delete later

    playerPool->getPoolEventDispatcher().addEventHandler(handler);

    auto playerPoolHandle = InterfaceToObject(playerPool, context, WRAPPED_METHODS(IPlayerPool));

    playerPool->addExtension(new IHandleStorage(context->GetIsolate(), playerPoolHandle), true);
}