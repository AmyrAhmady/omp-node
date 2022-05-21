#include "player_wrapper.hpp"
#include "../../logger.hpp"

#define ENTER_HANDLER(isolate, handler) \
    v8::Locker locker(isolate); \
    v8::Isolate::Scope isolateScope(isolate); \
    v8::HandleScope scope(isolate); \
    auto func = handler.Get(isolate); \
    v8::Local<v8::Context> context = func->GetCreationContext().ToLocalChecked(); \
    v8::Context::Scope contextScope(context);

//struct PlayerEventHandler {
//    virtual void onIncomingConnection(IPlayer& player, StringView ipAddress, unsigned short port) { }
//    virtual void onConnect(IPlayer& player) { }
//    virtual void onDisconnect(IPlayer& player, PeerDisconnectReason reason) { }
//    virtual bool onRequestSpawn(IPlayer& player) { return true; }
//    virtual void preSpawn(IPlayer& player) { }
//    virtual void onSpawn(IPlayer& player) { }
//    virtual void onStreamIn(IPlayer& player, IPlayer& forPlayer) { }
//    virtual void onStreamOut(IPlayer& player, IPlayer& forPlayer) { }
//    virtual bool onText(IPlayer& player, StringView message) { return true; }
//    virtual bool onCommandText(IPlayer& player, StringView message) { return false; }
//    virtual bool onShotMissed(IPlayer& player, const PlayerBulletData& bulletData) { return true; }
//    virtual bool onShotPlayer(IPlayer& player, IPlayer& target, const PlayerBulletData& bulletData) { return true; }
//    virtual bool onShotVehicle(IPlayer& player, IVehicle& target, const PlayerBulletData& bulletData) { return true; }
//    virtual bool onShotObject(IPlayer& player, IObject& target, const PlayerBulletData& bulletData) { return true; }
//    virtual bool onShotPlayerObject(IPlayer& player, IPlayerObject& target, const PlayerBulletData& bulletData) { return true; }
//    virtual void onScoreChange(IPlayer& player, int score) { }
//    virtual void onNameChange(IPlayer& player, StringView oldName) { }
//    virtual void onDeath(IPlayer& player, IPlayer* killer, int reason) { }
//    virtual void onTakeDamage(IPlayer& player, IPlayer* from, float amount, unsigned weapon, BodyPart part) { }
//    virtual void onGiveDamage(IPlayer& player, IPlayer& to, float amount, unsigned weapon, BodyPart part) { }
//    virtual void onInteriorChange(IPlayer& player, unsigned newInterior, unsigned oldInterior) { }
//    virtual void onStateChange(IPlayer& player, PlayerState newState, PlayerState oldState) { }
//    virtual void onKeyStateChange(IPlayer& player, uint32_t newKeys, uint32_t oldKeys) { }
//    virtual void onClickedMap(IPlayer& player, Vector3 pos) { }
//    virtual void onClickedPlayer(IPlayer& player, IPlayer& clicked, PlayerClickSource source) { }
//    virtual void onClientCheckResponse(IPlayer& player, int actionType, int address, int results) { }
//};

struct PlayerNodeJSEventHandler : PlayerEventHandler {
    v8::Isolate *isolate;
    v8::UniquePersistent<v8::Function> handler;

    PlayerNodeJSEventHandler(v8::Local<v8::Function> _handler) {
        isolate = _handler->GetIsolate();
        handler = v8::UniquePersistent<v8::Function>(isolate, _handler);
    }
};

struct PlayerIncomingConnectionHandler : PlayerNodeJSEventHandler {
    PlayerIncomingConnectionHandler(v8::Local<v8::Function> _handler)
        : PlayerNodeJSEventHandler(_handler) {
    }

    void onIncomingConnection(IPlayer &player, StringView ipAddress, unsigned short port) override {
        ENTER_HANDLER(isolate, handler);

        v8::Local<v8::Value> args[3];

        args[0] = GetHandleStorageExtension(&player)->get();
        args[1] = StringViewToJS(ipAddress, isolate);
        args[2] = UIntToJS(port, isolate);

        func->Call(context, context->Global(), 3, args).ToLocalChecked();
    }
};

void addEventHandler(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto dispatcher = GetContextExternalPointer<IEventDispatcher<PlayerEventHandler>>(info);

    auto event = JSToString(info[0], context);
    auto handler = info[1].As<v8::Function>();

    PlayerEventHandler *handlerObj; // todo: store this somewhere

    if (event == "incomingConnection") {
        handlerObj = new PlayerIncomingConnectionHandler(handler);
    } else {
        handlerObj = new PlayerEventHandler();
    }

    auto result = dispatcher->addEventHandler(handlerObj);

    info.GetReturnValue().Set(result);
}

void count(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto dispatcher = GetContextExternalPointer<IEventDispatcher<PlayerEventHandler>>(info);

    auto result = dispatcher->count();

    auto resultHandle = UIntToJS(result, isolate);

    info.GetReturnValue().Set(resultHandle);
}

v8::Local<v8::Value> WrapPlayerEventDispatcher(IEventDispatcher<PlayerEventHandler> *dispatcher,
                               v8::Local<v8::Context> context) {
    ObjectMethods methods = {{"addEventHandler", addEventHandler},
//                             {"removeEventHandler", removeEventHandler},
//                             {"hasEventHandler",    hasEventHandler},
                             {"count",           count}};

    v8::EscapableHandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(dispatcher, context, methods);

    return hs.Escape(dispatcherHandle);
}