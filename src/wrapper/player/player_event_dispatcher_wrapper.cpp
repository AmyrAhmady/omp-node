#include <utility>

#include "player_wrapper.hpp"
#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"

#define ENTER_HANDLER(isolate, handler) \
    v8::Locker locker(isolate); \
    v8::Isolate::Scope isolateScope(isolate); \
    v8::HandleScope scope(isolate); \
    auto func = handler.Get(isolate); \
    v8::Local<v8::Context> context = func->GetCreationContext().ToLocalChecked(); \
    v8::Context::Scope contextScope(context);

struct PlayerNodeJSEventHandler : PlayerEventHandler {
    Impl::String event;
    v8::Isolate *isolate;
    v8::UniquePersistent<v8::Function> handler;

    PlayerNodeJSEventHandler(Impl::String _event, v8::Local<v8::Function> _handler) {
        event = std::move(_event);
        isolate = _handler->GetIsolate();
        handler = v8::UniquePersistent<v8::Function>(isolate, _handler);
    }

public:
    Impl::String getEvent() const {
        return event;
    }

    v8::Local<v8::Value> getHandler() {
        v8::EscapableHandleScope hs(isolate);

        return hs.Escape(handler.Get(isolate));
    }
};

FlatPtrHashSet<PlayerNodeJSEventHandler> playerEventHandlers;

#define HANDLER(returnType, handlerFunctionName, argsCount, codeBlock, returnValue, ...) \
    struct H##_##handlerFunctionName : PlayerNodeJSEventHandler { \
        H##_##handlerFunctionName(Impl::String _event, v8::Local<v8::Function> _handler) : PlayerNodeJSEventHandler( \
            std::move(_event), \
            _handler) { \
        } \
        returnType handlerFunctionName(IPlayer &player, ##__VA_ARGS__) override { \
            ENTER_HANDLER(isolate, handler) \
            v8::Local<v8::Value> args[(argsCount) + 1]; \
            args[0] = GetHandleStorageExtension(&player)->get(); \
            codeBlock \
            auto cbReturnedValue = func->Call(context, context->Global(), (argsCount) + 1, args).ToLocalChecked();            \
            returnValue; \
        } \
    };

HANDLER(void, onIncomingConnection, 2, {
    args[1] = StringViewToJS(ipAddress, context);
    args[2] = UIntToJS(port, context);
}, return, StringView ipAddress, unsigned short port)

HANDLER(void, onPlayerConnect, 0, {
}, return)

HANDLER(void, onPlayerDisconnect, 1, {
    args[1] = UIntToJS(reason, context);
}, return, PeerDisconnectReason reason)

HANDLER(bool, onPlayerRequestSpawn, 0, {
}, return JSToBool(cbReturnedValue, context))

HANDLER(void, onBeforePlayerSpawn, 0, {
}, return)

HANDLER(void, onPlayerSpawn, 0, {
}, return)

HANDLER(void, onPlayerStreamIn, 1, {
    args[1] = GetHandleStorageExtension(&forPlayer)->get();
}, return, IPlayer &forPlayer)

HANDLER(void, onPlayerStreamOut, 1, {
    args[1] = GetHandleStorageExtension(&forPlayer)->get();
}, return, IPlayer &forPlayer)

HANDLER(bool, onPlayerText, 1, {
    args[1] = StringViewToJS(message, context);
}, return JSToBool(cbReturnedValue, context), StringView message)

HANDLER(bool, onPlayerCommandText, 1, {
    args[1] = StringViewToJS(message, context);
}, return JSToBool(cbReturnedValue, context), StringView message)

HANDLER(bool, onPlayerShotMissed, 1, {
    args[1] = PlayerBulletDataToJS(bulletData, context);
}, return JSToBool(cbReturnedValue, context), const PlayerBulletData &bulletData)

HANDLER(bool, onPlayerShotPlayer, 2, {
    args[1] = GetHandleStorageExtension(&target)->get();
    args[2] = PlayerBulletDataToJS(bulletData, context);
}, return JSToBool(cbReturnedValue, context), IPlayer &target, const PlayerBulletData &bulletData)

HANDLER(bool, onPlayerShotVehicle, 2, {
    args[1] = GetHandleStorageExtension(&target)->get();
    args[2] = PlayerBulletDataToJS(bulletData, context);
}, return JSToBool(cbReturnedValue, context), IVehicle &target, const PlayerBulletData &bulletData)

HANDLER(bool, onPlayerShotObject, 2, {
    args[1] = v8::Boolean::New(isolate, false); // todo
    args[2] = PlayerBulletDataToJS(bulletData, context);
}, return JSToBool(cbReturnedValue, context), IObject &target, const PlayerBulletData &bulletData)

HANDLER(bool, onPlayerShotPlayerObject, 2, {
    args[1] = v8::Boolean::New(isolate, false); // todo
    args[2] = PlayerBulletDataToJS(bulletData, context);
}, return JSToBool(cbReturnedValue, context), IPlayerObject &target, const PlayerBulletData &bulletData)

HANDLER(void, onPlayerScoreChange, 1, {
    args[1] = IntToJS(score, context);
}, return, int score)

HANDLER(void, onPlayerNameChange, 1, {
    args[1] = StringViewToJS(oldName, context);
}, return, StringView oldName)

HANDLER(void, onPlayerDeath, 2, {
    args[1] = GetHandleStorageExtension(killer)->get();
    args[2] = IntToJS(reason, context);
}, return, IPlayer *killer, int reason)

HANDLER(void, onPlayerTakeDamage, 4, {
    args[1] = GetHandleStorageExtension(from)->get();
    args[2] = FloatToJS(amount, context);
    args[3] = UIntToJS(weapon, context);
    args[4] = UIntToJS(part, context);
}, return, IPlayer *from, float amount, unsigned weapon, BodyPart part)

HANDLER(void, onPlayerGiveDamage, 4, {
    args[1] = GetHandleStorageExtension(&to)->get();
    args[2] = FloatToJS(amount, context);
    args[3] = UIntToJS(weapon, context);
    args[4] = UIntToJS(part, context);
}, return, IPlayer &to, float amount, unsigned weapon, BodyPart part)

HANDLER(void, onPlayerInteriorChange, 2, {
    args[1] = UIntToJS(newInterior, context);
    args[2] = UIntToJS(oldInterior, context);
}, return, unsigned newInterior, unsigned oldInterior)

HANDLER(void, onPlayerStateChange, 2, {
    args[1] = UIntToJS(newState, context);
    args[2] = UIntToJS(oldState, context);
}, return, PlayerState newState, PlayerState oldState)

HANDLER(void, onPlayerKeyStateChange, 2, {
    args[1] = UIntToJS(newKeys, context);
    args[2] = UIntToJS(oldKeys, context);
}, return, uint32_t newKeys, uint32_t oldKeys)

HANDLER(void, onPlayerClickMap, 1, {
    args[1] = Vector3ToJS(pos, context);
}, return, Vector3 pos)

HANDLER(void, onPlayerClickPlayer, 2, {
    args[1] = GetHandleStorageExtension(&clicked)->get();
    args[2] = UIntToJS(source, context);
}, return, IPlayer &clicked, PlayerClickSource source)

HANDLER(void, onClientCheckResponse, 3, {
    args[1] = IntToJS(actionType, context);
    args[2] = IntToJS(address, context);
    args[3] = IntToJS(results, context);
}, return, int actionType, int address, int results)

#define HANDLE(name) if (event == #name) { handlerObj = new H##_##name(event, handler); }

void addEventHandler(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto dispatcher = GetContextExternalPointer<IEventDispatcher<PlayerEventHandler>>(info);

    auto event = JSToString(info[0], context);
    auto handler = info[1].As<v8::Function>();
    auto priority = JSToInt(info[2], context, EventPriority_Default);

    if (!handler->IsFunction()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A function is required").ToLocalChecked()));
        return;
    }

    PlayerNodeJSEventHandler *handlerObj;

    HANDLE(onIncomingConnection) else HANDLE(onPlayerConnect) else HANDLE(onPlayerDisconnect) else HANDLE(
        onPlayerRequestSpawn) else HANDLE(onBeforePlayerSpawn) else HANDLE(onPlayerSpawn) else HANDLE(onPlayerStreamIn) else HANDLE(
        onPlayerStreamOut) else HANDLE(onPlayerText) else HANDLE(onPlayerCommandText) else HANDLE(onPlayerShotMissed) else HANDLE(
        onPlayerShotPlayer) else HANDLE(onPlayerShotVehicle) else HANDLE(onPlayerShotObject) else HANDLE(
        onPlayerShotPlayerObject) else HANDLE(onPlayerScoreChange) else HANDLE(onPlayerNameChange) else HANDLE(
        onPlayerDeath) else HANDLE(onPlayerTakeDamage) else HANDLE(onPlayerGiveDamage) else HANDLE(
        onPlayerInteriorChange) else HANDLE(onPlayerStateChange) else HANDLE(onPlayerKeyStateChange) else HANDLE(
        onPlayerClickMap) else HANDLE(onPlayerClickPlayer) else HANDLE(onClientCheckResponse) else {
        info.GetReturnValue().Set(false);
        return;
    }

    auto result = dispatcher->addEventHandler(handlerObj, (EventPriority)priority);

    info.GetReturnValue().Set(result);

    playerEventHandlers.emplace(handlerObj);
}

void hasEventHandler(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto dispatcher = GetContextExternalPointer<IEventDispatcher<PlayerEventHandler>>(info);

    auto event = JSToString(info[0], context);
    auto handler = info[1].As<v8::Function>();
    event_order_t priority = JSToInt(info[2], context);

    if (!handler->IsFunction()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A function is required").ToLocalChecked()));
        return;
    }

    for (auto handlerObj: playerEventHandlers) {
        if (handlerObj->getEvent() == event && handlerObj->getHandler() == handler) {
            auto result = dispatcher->hasEventHandler(handlerObj, priority);

            info.GetReturnValue().Set(result);

            return;
        }
    }

    info.GetReturnValue().Set(false);
}

void removeEventHandler(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto dispatcher = GetContextExternalPointer<IEventDispatcher<PlayerEventHandler>>(info);

    auto event = JSToString(info[0], context);
    auto handler = info[1].As<v8::Function>();

    if (!handler->IsFunction()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A function is required").ToLocalChecked()));
        return;
    }

    for (auto handlerObj: playerEventHandlers) {
        if (handlerObj->getEvent() == event && handlerObj->getHandler() == handler) {
            auto result = dispatcher->removeEventHandler(handlerObj);

            info.GetReturnValue().Set(result);

            if (result) {
                playerEventHandlers.erase(handlerObj);
            }

            return;
        }
    }

    info.GetReturnValue().Set(false);
}

void count(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto dispatcher = GetContextExternalPointer<IEventDispatcher<PlayerEventHandler>>(info);

    auto result = dispatcher->count();

    auto resultHandle = UIntToJS(result, context);

    info.GetReturnValue().Set(resultHandle);
}

v8::Local<v8::Value> WrapPlayerEventDispatcher(IEventDispatcher<PlayerEventHandler> *dispatcher,
                                               v8::Local<v8::Context> context) {
    ObjectMethods methods = {{"addEventHandler",    addEventHandler},
                             {"removeEventHandler", removeEventHandler},
                             {"hasEventHandler",    hasEventHandler},
                             {"count",              count}};

    v8::EscapableHandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(dispatcher, context, methods);

    return hs.Escape(dispatcherHandle);
}