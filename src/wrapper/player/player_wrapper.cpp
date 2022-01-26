#include "player_wrapper.hpp"
#include "../../logger.hpp"

void kick(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto player = GetContextExternalPointer<IPlayer>(info);

    player->kick();
}

void ban(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto player = GetContextExternalPointer<IPlayer>(info);

    StringView reason;

    if (!info[0]->IsUndefined()) {
        reason = JSToStringView(info[0], context);
    }

    player->ban(reason);
}

void setHealth(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto player = GetContextExternalPointer<IPlayer>(info);

    float health = JSToFloat(info[0], context);

    player->setHealth(health);
}

void getKeyData(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto player = GetContextExternalPointer<IPlayer>(info);

    auto keyData = player->getKeyData();

    info.GetReturnValue().Set(PlayerKeyDataToJS(keyData, context));
}

void WrapPlayer(HandleStorage &storage, IPlayer *player, v8::Local<v8::Context> context) {
    ObjectMethods methods = {
        {"kick", kick},
        {"ban", ban},
        {"setHealth", setHealth},
        {"getKeyData", getKeyData}
    };

    auto playerHandle = InterfaceToObject(storage, player, context, methods);

    storage.set(player, new v8::UniquePersistent<v8::Value>(context->GetIsolate(), playerHandle));
}