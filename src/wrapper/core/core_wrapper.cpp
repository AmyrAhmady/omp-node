#include "../player/player_pool_wrapper.hpp"
#include "core_wrapper.hpp"

WRAP_BASIC(ICore)

WRAP_BASIC_CALL_RETURN(ICore, getVersion, SemanticVersionToJS)
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
    auto coreHandle = InterfaceToObject(core, context, WRAPPED_METHODS(ICore));

    core->addExtension(new IHandleStorage(context->GetIsolate(), coreHandle), true);

    WrapConfig(&core->getConfig(), context);
    WrapPlayerPool(&core->getPlayers(), context);
}
