#include "player_wrapper.hpp"
#include "player_event_dispatcher_wrapper.hpp"
#include "../../logger.hpp"
#include "../primitive.hpp"

void entries(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto playerPool = GetContextExternalPointer<IPlayerPool>(info);

    auto entries = playerPool->entries();

    auto array = v8::Array::New(isolate, entries.size());

    unsigned index = 0;

    for (auto entry: entries) {
        auto playerHandle = GetHandleStorageExtension(entry)->get();

        array->Set(context, index++, playerHandle).Check();
    }

    info.GetReturnValue().Set(array);
}
void players(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto playerPool = GetContextExternalPointer<IPlayerPool>(info);

    auto entries = playerPool->players();

    auto array = v8::Array::New(isolate, entries.size());

    unsigned index = 0;

    for (auto entry: entries) {

        auto playerHandle = GetHandleStorageExtension(entry)->get();

        array->Set(context, index++, playerHandle).Check();
    }

    info.GetReturnValue().Set(array);
}
void bots(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto playerPool = GetContextExternalPointer<IPlayerPool>(info);

    auto entries = playerPool->bots();

    auto array = v8::Array::New(isolate, entries.size());

    unsigned index = 0;

    for (auto entry: entries) {

        auto playerHandle = GetHandleStorageExtension(entry)->get();

        array->Set(context, index++, playerHandle).Check();
    }

    info.GetReturnValue().Set(array);
}
void getEventDispatcher(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto playerPool = GetContextExternalPointer<IPlayerPool>(info);

    auto dispatcher = &playerPool->getEventDispatcher();

    auto dispatcherHandle = WrapPlayerEventDispatcher(&playerPool->getEventDispatcher(), context);

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

struct PlayerEntryHandler : PoolEventHandler<IPlayer> {
    v8::Isolate *isolate;
    v8::UniquePersistent<v8::Context> context;

    PlayerEntryHandler(v8::Local<v8::Context> _context)
        : isolate(_context->GetIsolate()), context(_context->GetIsolate(), _context) {
    }

    /// Called right after a new entry was constructed
    void onPoolEntryCreated(IPlayer &entry) override {
        L_DEBUG << "onPoolEntryCreated";
        v8::Locker locker(isolate);
        v8::Isolate::Scope isolateScope(isolate);

        v8::HandleScope scope(isolate);

        auto _context = context.Get(isolate);

        v8::Context::Scope contextScope(_context);

        WrapPlayer(&entry, _context);
    };

    /// Called just before an entry is destructed
    void onPoolEntryDestroyed(IPlayer &entry) override {
        v8::Locker locker(isolate);
        v8::Isolate::Scope isolateScope(isolate);

        v8::HandleScope scope(isolate);

        auto _context = context.Get(isolate);

        v8::Context::Scope contextScope(_context);

        auto handleStorage = GetHandleStorageExtension(&entry);

        if (handleStorage != nullptr) {
            auto entryHandle = handleStorage->get();

            entryHandle.As<v8::Object>()->SetInternalField(0, v8::External::New(isolate, nullptr));
        }
    };
};

PlayerEntryHandler *handler;

void WrapPlayerPool(IPlayerPool *playerPool, v8::Local<v8::Context> context) {
    handler = new PlayerEntryHandler(context); // todo: store somewhere to delete later

    playerPool->getPoolEventDispatcher().addEventHandler(handler);

    ObjectMethods methods = {{"entries",                entries},
                             {"players",                players},
                             {"bots",                   bots},
                             {"getEventDispatcher",     getEventDispatcher},
                             {"sendClientMessageToAll", sendClientMessageToAll}};

    auto playerPoolHandle = InterfaceToObject(playerPool, context, methods);

    playerPool->addExtension(new IHandleStorage(context->GetIsolate(), playerPoolHandle), true);
}