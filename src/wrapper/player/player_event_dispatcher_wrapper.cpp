#include <utility>

#include "player_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"
#include "../../converter/vehicle.hpp"
#include "../../converter/entity.hpp"
#include "player_event_dispatcher_wrapper.hpp"

WRAP_BASIC(IPlayerEventDispatcher)
WRAP_HANDLER_BASIC(PlayerEventHandler, NodeJSPlayerEventHandler)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onIncomingConnection, 3, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = StringViewToJS(ipAddress, context);
    args[2] = UIntToJS(port, context);
}, return, return, IPlayer &player, StringView ipAddress, unsigned short port)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onPlayerConnect, 1, {
    args[0] = GetHandleStorageExtension(&player)->get();
}, return, return, IPlayer &player)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onPlayerDisconnect, 2, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = EnumToJS(reason, context);
}, return, return, IPlayer &player, PeerDisconnectReason reason)

WRAP_HANDLER(NodeJSPlayerEventHandler, bool, onPlayerRequestSpawn, 1, {
    args[0] = GetHandleStorageExtension(&player)->get();
}, return JSToBool(cbReturnedValue, context), return true, IPlayer &player)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onBeforePlayerSpawn, 1, {
    args[0] = GetHandleStorageExtension(&player)->get();
}, return, return, IPlayer &player)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onPlayerSpawn, 1, {
    args[0] = GetHandleStorageExtension(&player)->get();
}, return, return, IPlayer &player)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onPlayerStreamIn, 2, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = GetHandleStorageExtension(&forPlayer)->get();
}, return, return, IPlayer &player, IPlayer &forPlayer)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onPlayerStreamOut, 2, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = GetHandleStorageExtension(&forPlayer)->get();
}, return, return, IPlayer &player, IPlayer &forPlayer)

WRAP_HANDLER(NodeJSPlayerEventHandler, bool, onPlayerText, 2, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = StringViewToJS(message, context);
}, return JSToBool(cbReturnedValue, context), return true, IPlayer &player, StringView message)

WRAP_HANDLER(NodeJSPlayerEventHandler, bool, onPlayerCommandText, 2, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = StringViewToJS(message, context);
}, return JSToBool(cbReturnedValue, context), return false, IPlayer &player, StringView message)

WRAP_HANDLER(NodeJSPlayerEventHandler, bool, onPlayerShotMissed, 2, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = PlayerBulletDataToJS(bulletData, context);
}, return JSToBool(cbReturnedValue, context), return true, IPlayer &player, const PlayerBulletData &bulletData)

WRAP_HANDLER(NodeJSPlayerEventHandler,
             bool,
             onPlayerShotPlayer,
             3,
             {
                 args[0] = GetHandleStorageExtension(&player)->get();
                 args[1] = EntityToJS<IPlayer>(target, context);
                 args[2] = PlayerBulletDataToJS(bulletData, context);
             },
             return JSToBool(cbReturnedValue, context),
             return true,
             IPlayer &player,
             IPlayer &target,
             const PlayerBulletData &bulletData)

WRAP_HANDLER(NodeJSPlayerEventHandler,
             bool,
             onPlayerShotVehicle,
             3,
             {
                 args[0] = GetHandleStorageExtension(&player)->get();
                 args[1] = EntityToJS<IVehicle>(target, context);
                 args[2] = PlayerBulletDataToJS(bulletData, context);
             },
             return JSToBool(cbReturnedValue, context),
             return true,
             IPlayer &player,
             IVehicle &target,
             const PlayerBulletData &bulletData)

WRAP_HANDLER(NodeJSPlayerEventHandler,
             bool,
             onPlayerShotObject,
             3,
             {
                 args[0] = GetHandleStorageExtension(&player)->get();
                 args[1] = v8::Boolean::New(isolate, false); // todo
                 args[2] = PlayerBulletDataToJS(bulletData, context);
             },
             return JSToBool(cbReturnedValue, context),
             return true,
             IPlayer &player,
             IObject &target,
             const PlayerBulletData &bulletData)

WRAP_HANDLER(NodeJSPlayerEventHandler,
             bool,
             onPlayerShotPlayerObject,
             3,
             {
                 args[0] = GetHandleStorageExtension(&player)->get();
                 args[1] = v8::Boolean::New(isolate, false); // todo
                 args[2] = PlayerBulletDataToJS(bulletData, context);
             },
             return JSToBool(cbReturnedValue, context),
             return true,
             IPlayer &player,
             IPlayerObject &target,
             const PlayerBulletData &bulletData)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onPlayerScoreChange, 2, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = IntToJS(score, context);
}, return, return, IPlayer &player, int score)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onPlayerNameChange, 2, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = StringViewToJS(oldName, context);
}, return, return, IPlayer &player, StringView oldName)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onPlayerDeath, 3, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = GetHandleStorageExtension(killer)->get();
    args[2] = IntToJS(reason, context);
}, return, return, IPlayer &player, IPlayer *killer, int reason)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onPlayerTakeDamage, 5, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = GetHandleStorageExtension(from)->get();
    args[2] = FloatToJS(amount, context);
    args[3] = UIntToJS(weapon, context);
    args[4] = EnumToJS(part, context);
}, return, return, IPlayer &player, IPlayer *from, float amount, unsigned weapon, BodyPart part)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onPlayerGiveDamage, 5, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = GetHandleStorageExtension(&to)->get();
    args[2] = FloatToJS(amount, context);
    args[3] = UIntToJS(weapon, context);
    args[4] = EnumToJS(part, context);
}, return, return, IPlayer &player, IPlayer &to, float amount, unsigned weapon, BodyPart part)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onPlayerInteriorChange, 3, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = UIntToJS(newInterior, context);
    args[2] = UIntToJS(oldInterior, context);
}, return, return, IPlayer &player, unsigned newInterior, unsigned oldInterior)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onPlayerStateChange, 3, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = EnumToJS(newState, context);
    args[2] = EnumToJS(oldState, context);
}, return, return, IPlayer &player, PlayerState newState, PlayerState oldState)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onPlayerKeyStateChange, 3, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = UIntToJS(newKeys, context);
    args[2] = UIntToJS(oldKeys, context);
}, return, return, IPlayer &player, uint32_t newKeys, uint32_t oldKeys)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onPlayerClickMap, 2, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = VectorToJS<Vector3>(pos, context);
}, return, return, IPlayer &player, Vector3 pos)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onPlayerClickPlayer, 3, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = GetHandleStorageExtension(&clicked)->get();
    args[2] = EnumToJS(source, context);
}, return, return, IPlayer &player, IPlayer &clicked, PlayerClickSource source)

WRAP_HANDLER(NodeJSPlayerEventHandler, void, onClientCheckResponse, 4, {
    args[0] = GetHandleStorageExtension(&player)->get();
    args[1] = IntToJS(actionType, context);
    args[2] = IntToJS(address, context);
    args[3] = IntToJS(results, context);
}, return, return, IPlayer &player, int actionType, int address, int results)

WRAP_BASIC_CODE(IPlayerEventDispatcher, addEventHandler, WRAP_ADD_EVENT_HANDLER(NodeJSPlayerEventHandler))

WRAP_BASIC_CODE(IPlayerEventDispatcher, hasEventHandler, WRAP_HAS_EVENT_HANDLER(NodeJSPlayerEventHandler))

WRAP_BASIC_CODE(IPlayerEventDispatcher, removeEventHandler, WRAP_REMOVE_EVENT_HANDLER(NodeJSPlayerEventHandler))

WRAP_BASIC_CALL_RETURN(IPlayerEventDispatcher, count, (size_t, UIntToJS))

v8::Local<v8::Value> WrapPlayerEventDispatcher(IEventDispatcher<PlayerEventHandler> *dispatcher,
                                               v8::Local<v8::Context> context) {

    v8::EscapableHandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(dispatcher, context, WRAPPED_METHODS(IPlayerEventDispatcher));

    return hs.Escape(dispatcherHandle);
}