#include "player_wrapper.hpp"
#include "player_event_dispatcher_wrapper.hpp"
#include "../../logger.hpp"

void entries(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto storage = GetContextHandleStorage(info);
    auto playerPool = GetContextExternalPointer<IPlayerPool>(info);

    auto entries = playerPool->entries();

    auto array = v8::Array::New(isolate, entries.size());

    unsigned index = 0;

    for (auto entry: entries) {
        auto playerHandle = storage->get(entry)->Get(isolate);

        array->Set(context, index++, playerHandle).Check();
    }

    info.GetReturnValue().Set(array);
}
void players(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto storage = GetContextHandleStorage(info);
    auto playerPool = GetContextExternalPointer<IPlayerPool>(info);

    auto entries = playerPool->players();

    auto array = v8::Array::New(isolate, entries.size());

    unsigned index = 0;

    for (auto entry: entries) {

        auto playerHandle = storage->get(entry)->Get(isolate);

        array->Set(context, index++, playerHandle).Check();
    }

    info.GetReturnValue().Set(array);
}
void bots(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto storage = GetContextHandleStorage(info);
    auto playerPool = GetContextExternalPointer<IPlayerPool>(info);

    auto entries = playerPool->bots();

    auto array = v8::Array::New(isolate, entries.size());

    unsigned index = 0;

    for (auto entry: entries) {

        auto playerHandle = storage->get(entry)->Get(isolate);

        array->Set(context, index++, playerHandle).Check();
    }

    info.GetReturnValue().Set(array);
}
void getEventDispatcher(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto storage = GetContextHandleStorage(info);
    auto playerPool = GetContextExternalPointer<IPlayerPool>(info);

    auto dispatcher = &playerPool->getEventDispatcher();

    auto dispatcherHandle = storage->get(dispatcher)->Get(isolate);

    info.GetReturnValue().Set(dispatcherHandle);
}

void sendClientMessageToAll(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto playerPool = GetContextExternalPointer<IPlayerPool>(info);

    int colorRGBA = JSToInt(info[0], context);
    auto message = JSToString(info[1], context);

    Colour color = Colour::FromRGBA(colorRGBA);

    playerPool->sendClientMessageToAll(color, message);
}

struct PlayerEntryHandler : PlayerEventHandler {
    HandleStorage *storage;
    v8::Isolate *isolate;
    v8::UniquePersistent<v8::Context> context;

    PlayerEntryHandler(HandleStorage &_storage, v8::Local<v8::Context> _context)
        : storage(&_storage), isolate(_context->GetIsolate()), context(_context->GetIsolate(), _context) {
    }

    void onIncomingConnection(IPlayer &player, StringView ipAddress, unsigned short port) override {
        v8::Locker locker(isolate);
        v8::Isolate::Scope isolateScope(isolate);

        v8::HandleScope scope(isolate);

        auto _context = context.Get(isolate);

        v8::Context::Scope contextScope(_context);

        WrapPlayer(*storage, &player, _context);
    }

    void onPlayerDisconnect(IPlayer &player, PeerDisconnectReason reason) override {
        v8::Locker locker(isolate);
        v8::Isolate::Scope isolateScope(isolate);

        v8::HandleScope scope(isolate);

        auto _context = context.Get(isolate);

        v8::Context::Scope contextScope(_context);

        auto playerPersistentHandle = storage->get(&player);

        if (playerPersistentHandle != nullptr) {
            auto playerHandle = playerPersistentHandle->Get(isolate);

            playerHandle.As<v8::Object>()->SetInternalField(1, v8::External::New(isolate, nullptr));

            storage->remove(&player);
        }
    }
};

PlayerEntryHandler *handler;

void WrapPlayerPool(HandleStorage &storage, IPlayerPool *playerPool, v8::Local<v8::Context> context) {
    handler = new PlayerEntryHandler(storage, context); // todo: store somewhere to delete later

    playerPool->getEventDispatcher().addEventHandler(handler);

    ObjectMethods methods = {{"entries",                entries},
                             {"players",                players},
                             {"bots",                   bots},
                             {"getEventDispatcher",     getEventDispatcher},
                             {"sendClientMessageToAll", sendClientMessageToAll}};

    auto playerPoolHandle = InterfaceToObject(storage, playerPool, context, methods);
    storage.set(playerPool, new v8::UniquePersistent<v8::Value>(context->GetIsolate(), playerPoolHandle));

    WrapPlayerEventDispatcher(storage, &playerPool->getEventDispatcher(), context);
}