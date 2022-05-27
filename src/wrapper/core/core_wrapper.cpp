#include "../player/player_pool_wrapper.hpp"
#include "core_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"

WRAP_BASIC(ICore)

WRAP_BASIC_CALL_RETURN(ICore, getVersion, (SemanticVersion, TO_JS_FN(SemanticVersion)))
WRAP_BASIC_CALL_RETURN(ICore, getNetworkBitStreamVersion, (int, IntToJS))
WRAP_HANDLE_STORAGE_GET(ICore, getPlayers)
//WRAP_BASIC_CALL_RETURN(ICore, getEventDispatcher, (IEventDispatcher<CoreEventHandler>&, TO_JS_FN(IEventDispatcher<CoreEventHandler>)))
WRAP_HANDLE_STORAGE_GET(ICore, getConfig)
//WRAP_BASIC_CALL_RETURN(ICore, getNetworks, (const FlatPtrHashSet<INetwork>&, TO_JS_FN(FlatPtrHashSet<INetwork>)))
WRAP_BASIC_CALL_RETURN(ICore, getTickCount, (unsigned, UIntToJS))
WRAP_BASIC_CALL(ICore, setGravity, (float, JSToFloat, gravity))
WRAP_BASIC_CALL_RETURN(ICore, getGravity, (float, FloatToJS))
WRAP_BASIC_CALL(ICore, setWeather, (int, JSToInt, weather))
WRAP_BASIC_CALL(ICore, setWorldTime, (Hours, FROM_JS_FN(Hours), time))
WRAP_BASIC_CALL(ICore, useStuntBonuses, (bool, JSToBool, enable))
WRAP_BASIC_CALL(ICore,
                setData,
                (SettableCoreDataType, JSToEnum<SettableCoreDataType>, type),
                (Impl::String, FROM_JS_FN(String), data))
WRAP_BASIC_CALL(ICore, resetAll)
WRAP_BASIC_CALL(ICore, reloadAll)
WRAP_BASIC_CALL_RETURN(ICore,
                       getWeaponName,
                       (StringView, TO_JS_FN(StringView)),
                       (PlayerWeapon, JSToEnum<PlayerWeapon>, weapon))
WRAP_BASIC_CALL(ICore, connectBot, (Impl::String, FROM_JS_FN(String), name), (Impl::String, FROM_JS_FN(String), script))
//WRAP_BASIC_CALL(ICore, requestHTTP, (HTTPResponseHandler*, FROM_JS_FN(HTTPResponseHandler), handler), PARAMETERS(, HTTPRequestType type, StringView url, StringView data = StringView()))
WRAP_BASIC_CALL_RETURN(ICore, tickRate, (unsigned, UIntToJS))

void WrapCore(ICore *core, v8::Local<v8::Context> context) {
    auto coreHandle = InterfaceToObject(core, context, WRAPPED_METHODS(ICore));

    core->addExtension(new IHandleStorage(context->GetIsolate(), coreHandle), true);

    WrapConfig(&core->getConfig(), context);
    WrapPlayerPool(&core->getPlayers(), context);
}
