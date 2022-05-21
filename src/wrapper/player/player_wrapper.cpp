#include "player_wrapper.hpp"
#include "../../logger.hpp"

IPlayer *GetPlayerFromContext(const v8::FunctionCallbackInfo<v8::Value> &info) {
    auto player = GetContextExternalPointer<IPlayer>(info);

    if (player == nullptr) {
        info.GetIsolate()->ThrowException(v8::Exception::ReferenceError(v8::String::NewFromUtf8(info.GetIsolate(),
                                                                                                "The player is not connected").ToLocalChecked()));
    }

    return player;
}

void kick(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto player = GetPlayerFromContext(info);

    if (!player)
        return;

    player->kick();
}

void ban(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto player = GetPlayerFromContext(info);

    if (!player)
        return;

    Impl::String reason;

    if (!info[0]->IsUndefined()) {
        reason = JSToString(info[0], context);
    }

    player->ban(reason);
}

void setHealth(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto player = GetPlayerFromContext(info);

    if (!player)
        return;

    float health = JSToFloat(info[0], context);

    player->setHealth(health);
}

void getHealth(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto player = GetPlayerFromContext(info);

    if (!player)
        return;

    auto health = player->getHealth();

    info.GetReturnValue().Set(FloatToJS(health, isolate));
}

void getKeyData(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto player = GetPlayerFromContext(info);

    if (!player)
        return;

    auto keyData = player->getKeyData();

    info.GetReturnValue().Set(PlayerKeyDataToJS(keyData, context));
}

void WrapPlayer(IPlayer *player, v8::Local<v8::Context> context) {
    ObjectMethods methods = {{"kick",       kick},
                             {"ban",        ban},
                             {"setHealth",  setHealth},
                             {"getHealth",  getHealth},
                             {"getKeyData", getKeyData}};

    auto playerHandle = InterfaceToObject(player, context, methods);

    player->addExtension(new IHandleStorage(context->GetIsolate(), playerHandle), true);
}