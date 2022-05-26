#include "../../logger.hpp"
#include "vehicle_pool_wrapper.hpp"
#include "vehicle_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/vehicle.hpp"
#include "../entry_handler.hpp"
#include "vehicle_event_dispatcher_wrapper.hpp"
#include "vehicle_pool_event_dispatcher_wrapper.hpp"

WRAP_BASIC(IVehiclesComponent)

WRAP_BASIC_CALL_RETURN(IVehiclesComponent, models, (VehicleModels & , TO_JS_FN(VehicleModels)))

WRAP_BASIC_CALL_RETURN(IVehiclesComponent,
                       create,
                       (IVehicle * , TO_JS_FN(IVehicle)),
                       (bool, JSToBool, isStatic),
                       (int, JSToInt, modelID),
                       (Vector3, JSToVector<Vector3>, position),
                       (float, JSToFloat, Z, 0.0f),
                       (int, JSToInt, colour1, -1),
                       (int, JSToInt, colour2, -1),
                       (Seconds, JSToSeconds, respawnDelay, Seconds(-1)),
                       (bool, JSToBool, addSiren, false))

WRAP_BASIC_CODE(IVehiclesComponent, getEventDispatcher, {
    ENTER_FUNCTION_CALLBACK(info)
    auto pool = GetContextExternalPointer<IVehiclesComponent>(info);
    auto dispatcher = &pool->getEventDispatcher();
    auto dispatcherHandle = WrapVehicleEventDispatcher(dispatcher, context);
    info.GetReturnValue().Set(dispatcherHandle);
})
WRAP_BASIC_CODE(IVehiclesComponent, getPoolEventDispatcher, {
    ENTER_FUNCTION_CALLBACK(info)
    auto pool = GetContextExternalPointer<IVehiclesComponent>(info);
    auto dispatcher = &pool->getPoolEventDispatcher();
    auto dispatcherHandle = WrapVehiclePoolEventDispatcher(dispatcher, context);
    info.GetReturnValue().Set(dispatcherHandle);
})

NodeJSEntryHandler<IVehicle> *handler;

void WrapVehiclePool(IVehiclesComponent *vehiclePool, v8::Local<v8::Context> context) {
    handler = new NodeJSEntryHandler<IVehicle>(context, WrapVehicle); // todo: store somewhere to delete later

    vehiclePool->getPoolEventDispatcher().addEventHandler(handler);

    auto vehiclePoolHandle = InterfaceToObject(vehiclePool, context, WRAPPED_METHODS(IVehiclesComponent));

    vehiclePool->addExtension(new IHandleStorage(context->GetIsolate(), vehiclePoolHandle), true);
}