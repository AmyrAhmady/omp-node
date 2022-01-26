#include "../player/player_pool_wrapper.hpp"
#include "core_wrapper.hpp"

void getVersion(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto core = GetContextExternalPointer<ICore>(info);

    auto version = core->getVersion();

    auto versionObjectTemplate = v8::ObjectTemplate::New(isolate);

    versionObjectTemplate->Set(v8::String::NewFromUtf8(isolate, "major").ToLocalChecked(),
                               v8::Integer::New(isolate, version.major));
    versionObjectTemplate->Set(v8::String::NewFromUtf8(isolate, "minor").ToLocalChecked(),
                               v8::Integer::New(isolate, version.minor));
    versionObjectTemplate->Set(v8::String::NewFromUtf8(isolate, "patch").ToLocalChecked(),
                               v8::Integer::New(isolate, version.patch));
    versionObjectTemplate->Set(v8::String::NewFromUtf8(isolate, "prerel").ToLocalChecked(),
                               v8::Integer::New(isolate, version.prerel));

    auto returnObject = versionObjectTemplate->NewInstance(context);

    info.GetReturnValue().Set(returnObject.ToLocalChecked());
}

void getConfig(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto storage = GetContextHandleStorage(info);
    auto core = GetContextExternalPointer<ICore>(info);

    auto config = &core->getConfig();

    auto configHandle = storage->get(config)->Get(isolate);

    info.GetReturnValue().Set(configHandle);
}

void getPlayers(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto storage = GetContextHandleStorage(info);
    auto core = GetContextExternalPointer<ICore>(info);

    auto playerPool = &core->getPlayers();

    auto playerPoolHandle = storage->get(playerPool)->Get(isolate);

    info.GetReturnValue().Set(playerPoolHandle);
}

void getTickCount(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto core = GetContextExternalPointer<ICore>(info);

    auto tickCount = core->getTickCount();

    auto tickCountHandle = v8::Integer::New(isolate, tickCount);

    info.GetReturnValue().Set(tickCountHandle);
}

void setGravity(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto core = GetContextExternalPointer<ICore>(info);

    auto gravity = JSToFloat(info[0], context);

    core->setGravity(gravity);
}

void WrapCore(HandleStorage &storage, ICore *core, v8::Local<v8::Context> context) {
    ObjectMethods methods = {{"getVersion", getVersion}, {"getPlayers", getPlayers}, {"getConfig", getConfig},
                             {"getTickCount", getTickCount}, {"setGravity", setGravity}};
    auto coreHandle = InterfaceToObject(storage, core, context, methods);

    storage.set(core, new v8::UniquePersistent<v8::Value>(context->GetIsolate(), coreHandle));

    WrapConfig(storage, &core->getConfig(), context);
    WrapPlayerPool(storage, &core->getPlayers(), context);
}
