#include "player_wrapper.hpp"
#include "player_event_dispatcher_wrapper.hpp"
#include "player_update_event_dispatcher_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/player.hpp"
#include "../../converter/types.hpp"
#include "../../converter/entity.hpp"
#include "../entry_handler.hpp"
#include "../pool/read_only_pool_wrapper.hpp"
#include "../pool/pool_event_dispatcher_wrapper.hpp"

WRAP_BASIC(IPlayerPool)

WRAP_BASIC_CALL_RETURN(IPlayerPool, entries, (FlatPtrHashSetIPlayer, TO_JS_FN(FlatPtrHashSetIPlayer)))
WRAP_BASIC_CALL_RETURN(IPlayerPool, players, (FlatPtrHashSetIPlayer, TO_JS_FN(FlatPtrHashSetIPlayer)))
WRAP_BASIC_CALL_RETURN(IPlayerPool, bots, (FlatPtrHashSetIPlayer, TO_JS_FN(FlatPtrHashSetIPlayer)))
WRAP_BASIC_CALL_RETURN(IPlayerPool,
                       isNameTaken,
                       (bool, BoolToJS),
                       (Impl::String, JSToString, name),
                       (const IPlayer*, JSToEntity<IPlayer>, skip))
WRAP_BASIC_CALL(IPlayerPool,
                sendClientMessageToAll,
                (const Colour&, FROM_JS_FN(Colour), colour),
                (Impl::String, JSToString, message))
WRAP_BASIC_CALL(IPlayerPool,
                sendChatMessageToAll,
                (IPlayer & , JSToEntityRef<IPlayer>, from),
                (Impl::String, JSToString, message))
WRAP_BASIC_CALL(IPlayerPool,
                sendGameTextToAll,
                (Impl::String, JSToString, message),
                (Milliseconds, FROM_JS_FN(Milliseconds), time),
                (int, JSToInt, style))
WRAP_BASIC_CALL(IPlayerPool,
                sendDeathMessageToAll,
                (IPlayer * , JSToEntity<IPlayer>, killer),
                (IPlayer & , JSToEntityRef<IPlayer>, killee),
                (int, JSToInt, weapon))
WRAP_BASIC_CALL(IPlayerPool, sendEmptyDeathMessageToAll)
WRAP_BASIC_CALL(IPlayerPool,
                createExplosionForAll,
                (Vector3, JSToVector<Vector3>, vec),
                (int, JSToInt, type),
                (float, JSToFloat, radius))
WRAP_BASIC_CALL_RETURN(IPlayerPool, isNameValid, (bool, BoolToJS), (Impl::String, JSToString, name))
WRAP_BASIC_CALL(IPlayerPool, allowNickNameCharacter, (char, JSToChar, character), (bool, JSToBool, allow))
WRAP_BASIC_CALL_RETURN(IPlayerPool, isNickNameCharacterAllowed, (bool, BoolToJS), (char, JSToChar, character))

WRAP_LOCAL_EXT_HANDLE_STORAGE_GET(IPlayerPool, getEventDispatcher, EventDispatcherHandleStorage)

WRAP_LOCAL_EXT_HANDLE_STORAGE_GET(IPlayerPool, getPlayerUpdateDispatcher, PlayerUpdateEventDispatcherHandleStorage)

WRAP_POOL_EVENT_DISPATCHER(IPlayerPool, IPlayer)

WRAP_LOCAL_EXT_HANDLE_STORAGE_GET(IPlayerPool, getPoolEventDispatcher, PoolEventDispatcherHandleStorage)

WRAP_READ_ONLY_POOL_METHODS(IPlayerPool, IPlayer, EntityToJS<IPlayer>)

NodeJSEntryHandler<IPlayer> *handler;

class TestEventHandler : public PlayerEventHandler {
public:
    IPlayerPool *pool;
    explicit TestEventHandler(IPlayerPool *_pool): pool(_pool), PlayerEventHandler() {}

    void onPlayerConnect(IPlayer &player) override {
        pool->getEventDispatcher().addEventHandler(new PlayerEventHandler());
    }
};

void WrapPlayerPool(IPlayerPool *playerPool, v8::Local<v8::Context> context) {
    playerPool->getEventDispatcher().addEventHandler(new TestEventHandler(playerPool));

    handler = new NodeJSEntryHandler<IPlayer>(context, WrapPlayer);
    playerPool->getPoolEventDispatcher().addEventHandler(handler);
    playerPool->addExtension(handler, true);

    auto playerPoolHandle = InterfaceToObject(playerPool, context, WRAPPED_METHODS(IPlayerPool));
    playerPool->addExtension(new IHandleStorage(context->GetIsolate(), playerPoolHandle), true);

    auto eventDispatcherHandleStorage = WrapPlayerEventDispatcher(&playerPool->getEventDispatcher(), context);
    playerPool->addExtension(eventDispatcherHandleStorage, true);

    auto updateEventDispatcherHandleStorage =
        WrapPlayerUpdateEventDispatcher(&playerPool->getPlayerUpdateDispatcher(), context);
    playerPool->addExtension(updateEventDispatcherHandleStorage, true);

    auto poolEventDispatcherHandleStorage =
        WRAPPED_POOL_EVENT_DISPATCHER(IPlayer)(&playerPool->getPoolEventDispatcher(), context);
    playerPool->addExtension(poolEventDispatcherHandleStorage, true);
}