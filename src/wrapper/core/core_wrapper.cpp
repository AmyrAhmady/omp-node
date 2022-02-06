#include "../player/player_pool_wrapper.hpp"
#include "core_wrapper.hpp"

void getVersion(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto core = GetContextExternalPointer<ICore>(info);

    auto version = core->getVersion();

    auto versionObjectTemplate = v8::ObjectTemplate::New(isolate);

    versionObjectTemplate->Set(v8::String::NewFromUtf8(isolate, "major").ToLocalChecked(),
                               v8::Integer::NewFromUnsigned(isolate, version.major));
    versionObjectTemplate->Set(v8::String::NewFromUtf8(isolate, "minor").ToLocalChecked(),
                               v8::Integer::NewFromUnsigned(isolate, version.minor));
    versionObjectTemplate->Set(v8::String::NewFromUtf8(isolate, "patch").ToLocalChecked(),
                               v8::Integer::NewFromUnsigned(isolate, version.patch));
    versionObjectTemplate->Set(v8::String::NewFromUtf8(isolate, "prerel").ToLocalChecked(),
                               v8::Integer::NewFromUnsigned(isolate, version.prerel));

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

    auto tickCountHandle = UIntToJS(tickCount, isolate);

    info.GetReturnValue().Set(tickCountHandle);
}

void setGravity(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto core = GetContextExternalPointer<ICore>(info);

    auto gravity = JSToFloat(info[0], context);

    core->setGravity(gravity);
}

void setWeather(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto core = GetContextExternalPointer<ICore>(info);

    auto weather = JSToInt(info[0], context);

    core->setWeather(weather);
}

void setWorldTime(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto core = GetContextExternalPointer<ICore>(info);

    auto hoursCount = JSToInt(info[0], context);

    Hours hours(hoursCount);

    core->setWorldTime(hours);
}

void toggleStuntBonus(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto core = GetContextExternalPointer<ICore>(info);

    auto toggle = JSToBool(info[0], context);

    core->toggleStuntBonus(toggle);
}

void setData(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto core = GetContextExternalPointer<ICore>(info);

    auto data = JSToInt(info[0], context);
    auto value = JSToStringView(info[1], context);

    core->setData((SettableCoreDataType)data, value);
}

void getWeaponName(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto core = GetContextExternalPointer<ICore>(info);

    auto playerWeapon = JSToInt(info[0], context);

    auto weaponName = core->getWeaponName(static_cast<PlayerWeapon>(playerWeapon));

    auto weaponNameHandle = StringViewToJS(weaponName, isolate);

    info.GetReturnValue().Set(weaponNameHandle);
}

void tickRate(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto core = GetContextExternalPointer<ICore>(info);

    auto tickRate = core->tickRate();

    auto tickRateHandle = UIntToJS(tickRate, isolate);

    info.GetReturnValue().Set(tickRateHandle);
}

void WrapCore(HandleStorage &storage, ICore *core, v8::Local<v8::Context> context) {
    ObjectMethods methods = {{"getVersion",       getVersion},
                             {"getPlayers",       getPlayers},
                             {"getConfig",        getConfig},
                             {"getTickCount",     getTickCount},
                             {"setGravity",       setGravity},
                             {"setWeather",       setWeather},
                             {"setWorldTime",     setWorldTime},
                             {"toggleStuntBonus", toggleStuntBonus},
                             {"setData",          setData},
                             {"getWeaponName",    getWeaponName},
                             {"tickRate",    tickRate}};
    auto coreHandle = InterfaceToObject(storage, core, context, methods);

    storage.set(core, new v8::UniquePersistent<v8::Value>(context->GetIsolate(), coreHandle));

    WrapConfig(storage, &core->getConfig(), context);
    WrapPlayerPool(storage, &core->getPlayers(), context);
}
