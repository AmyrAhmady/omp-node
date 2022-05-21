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

WRAP_HANDLE_STORAGE_GET(ICore, getConfig)
WRAP_HANDLE_STORAGE_GET(ICore, getPlayers)

WRAP_BASIC_CALL_RETURN(ICore, getTickCount, UIntToJS)

WRAP_BASIC_CALL(ICore, setGravity, JSToFloat(info[0], context))

WRAP_BASIC_CALL_RETURN(ICore, getGravity, FloatToJS)

WRAP_BASIC_CALL(ICore, setWeather, JSToInt(info[0], context))

WRAP_BASIC_CALL(ICore, setWorldTime, Hours(JSToInt(info[0], context)))

WRAP_BASIC_CALL(ICore, useStuntBonuses, JSToBool(info[0], context))

WRAP_BASIC_CALL(ICore, setData, (SettableCoreDataType)JSToInt(info[0], context), JSToString(info[1], context))

WRAP_BASIC_CALL_RETURN(ICore, getWeaponName, StringViewToJS, static_cast<PlayerWeapon>(JSToInt(info[0], context)))

WRAP_BASIC_CALL_RETURN(ICore, tickRate, UIntToJS)

void WrapCore(ICore *core, v8::Local<v8::Context> context) {
    ObjectMethods methods = {{"getVersion",      getVersion},
                             {"getPlayers",      getPlayers},
                             {"getConfig",       getConfig},
                             {"getTickCount",    getTickCount},
                             {"getGravity",      getGravity},
                             {"setWeather",      setWeather},
                             {"setGravity",      setGravity},
                             {"setWorldTime",    setWorldTime},
                             {"useStuntBonuses", useStuntBonuses},
                             {"setData",         setData},
                             {"getWeaponName",   getWeaponName},
                             {"tickRate",        tickRate}};
    auto coreHandle = InterfaceToObject(core, context, methods);

    core->addExtension(new IHandleStorage(context->GetIsolate(), coreHandle), true);

    WrapConfig(&core->getConfig(), context);
    WrapPlayerPool(&core->getPlayers(), context);
}
