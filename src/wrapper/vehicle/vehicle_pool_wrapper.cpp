#include "../../logger.hpp"
#include "vehicle_pool_wrapper.hpp"
#include "vehicle_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/vehicle.hpp"
#include "../entry_handler.hpp"
#include "vehicle_event_dispatcher_wrapper.hpp"

WRAP_BASIC(IVehiclesComponent)

WRAP_BASIC_CALL_RETURN(IVehiclesComponent,
                       create,
                       IVehicleToJS,
                       JSToBool(info[0], context),
                       JSToInt(info[1], context),
                       JSToVector3(info[2], context),
                       JSToFloat(info[3], context),
                       JSToInt(info[4], context),
                       JSToInt(info[5], context),
                       JSToSeconds(info[6], context),
                       JSToBool(info[7], context))

WRAP_BASIC_CODE(IVehiclesComponent, getEventDispatcher, {
    ENTER_FUNCTION_CALLBACK(info)
    auto pool = GetContextExternalPointer<IVehiclesComponent>(info);
    auto dispatcher = &pool->getEventDispatcher();
    auto dispatcherHandle = WrapVehicleEventDispatcher(dispatcher, context);
    info.GetReturnValue().Set(dispatcherHandle);
})

NodeJSEntryHandler<IVehicle> *handler;

void WrapVehiclePool(IVehiclesComponent *vehiclePool, v8::Local<v8::Context> context) {
    handler = new NodeJSEntryHandler<IVehicle>(context, WrapVehicle); // todo: store somewhere to delete later

    vehiclePool->getPoolEventDispatcher().addEventHandler(handler);

    auto vehiclePoolHandle = InterfaceToObject(vehiclePool, context, WRAPPED_METHODS(IVehiclesComponent));

    vehiclePool->addExtension(new IHandleStorage(context->GetIsolate(), vehiclePoolHandle), true);
}