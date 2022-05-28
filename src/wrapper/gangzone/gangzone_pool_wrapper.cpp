#include "../../logger.hpp"
#include "gangzone_pool_wrapper.hpp"
#include "gangzone_wrapper.hpp"
#include "gangzone_event_dispatcher_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/gangzone.hpp"
#include "../../converter/entity.hpp"
#include "../entry_handler.hpp"
#include "../pool/read_only_pool_wrapper.hpp"
#include "../pool/pool_wrapper.hpp"

WRAP_BASIC(IGangZonesComponent)

WRAP_BASIC_CALL_RETURN(IGangZonesComponent,
                       create,
                       (IGangZone * , EntityToJS<IGangZone>),
                       (GangZonePos, FROM_JS_FN(GangZonePos), pos))

WRAP_BASIC_CALL_RETURN(IGangZonesComponent,
                       getCheckingGangZones,
                       (const FlatPtrHashSetIGangZone&, TO_JS_FN(FlatPtrHashSetIGangZone)))

WRAP_BASIC_CALL(IGangZonesComponent,
                useGangZoneCheck,
                (IGangZone & , JSToEntityRef<IGangZone>, zone),
                (bool, JSToBool, enable))

WRAP_BASIC_CODE(IGangZonesComponent, getEventDispatcher, {
    ENTER_FUNCTION_CALLBACK(info)
    auto pool = GetContextExternalPointer<IGangZonesComponent>(info);
    auto dispatcher = &pool->getEventDispatcher();
    auto dispatcherHandle = WrapGangZoneEventDispatcher(dispatcher, context);
    info.GetReturnValue().Set(dispatcherHandle);
})

WRAP_READ_ONLY_POOL_METHODS(IGangZonesComponent, IGangZone, EntityToJS<IGangZone>)
WRAP_POOL_METHODS(IGangZonesComponent, IGangZone)

NodeJSEntryHandler<IGangZone> *handler;

void WrapGangZonePool(IGangZonesComponent *gangZonePool, v8::Local<v8::Context> context) {
    handler = new NodeJSEntryHandler<IGangZone>(context, WrapGangZone); // todo: store somewhere to delete later

    gangZonePool->getPoolEventDispatcher().addEventHandler(handler);

    auto gangZonePoolHandle = InterfaceToObject(gangZonePool, context, WRAPPED_METHODS(IGangZonesComponent));

    gangZonePool->addExtension(new IHandleStorage(context->GetIsolate(), gangZonePoolHandle), true);
}