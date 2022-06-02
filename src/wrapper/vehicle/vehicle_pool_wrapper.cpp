#include "../../logger.hpp"
#include "vehicle_pool_wrapper.hpp"
#include "vehicle_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/vehicle.hpp"
#include "../../converter/entity.hpp"
#include "../entry_handler.hpp"
#include "vehicle_event_dispatcher_wrapper.hpp"
#include "../pool/read_only_pool_wrapper.hpp"
#include "../pool/pool_wrapper.hpp"
#include "../pool/pool_event_dispatcher_wrapper.hpp"

WRAP_BASIC(IVehiclesComponent)

WRAP_BASIC_CALL_RETURN(IVehiclesComponent, models, (VehicleModels & , TO_JS_FN(VehicleModels)))

WRAP_BASIC_CALL_RETURN_OVERLOAD(IVehiclesComponent,
                                create,
                                (create, info[0]->IsObject(), (IVehicle
                                    * , EntityToJS<IVehicle>),(const VehicleSpawnData&, FROM_JS_FN(VehicleSpawnData), data)),
                                (create, true, (IVehicle
                                    * , EntityToJS<IVehicle>), (bool, JSToBool, isStatic), (int, JSToInt, modelID), (Vector3, JSToVector<
                                    Vector3>, position), (float, JSToFloat, Z, 0.0f), (int, JSToInt, colour1, -1), (int, JSToInt, colour2, -1), (Seconds, JSToSeconds, respawnDelay, Seconds(
                                    -1)), (bool, JSToBool, addSiren, false)))

WRAP_LOCAL_EXT_HANDLE_STORAGE_GET(IVehiclesComponent, getEventDispatcher, EventDispatcherHandleStorage)

WRAP_READ_ONLY_POOL_METHODS(IVehiclesComponent, IVehicle, EntityToJS<IVehicle>)
WRAP_POOL_METHODS(IVehiclesComponent, IVehicle)

NodeJSEntryHandler<IVehicle> *handler;

void WrapVehiclePool(IVehiclesComponent *vehiclePool, v8::Local<v8::Context> context) {
    handler = new NodeJSEntryHandler<IVehicle>(context, WrapVehicle);
    vehiclePool->getPoolEventDispatcher().addEventHandler(handler);
    vehiclePool->addExtension(handler, true);

    auto vehiclePoolHandle = InterfaceToObject(vehiclePool, context, WRAPPED_METHODS(IVehiclesComponent));
    vehiclePool->addExtension(new IHandleStorage(context->GetIsolate(), vehiclePoolHandle), true);

    auto eventDispatcherHandleStorage = WrapVehicleEventDispatcher(&vehiclePool->getEventDispatcher(), context);
    vehiclePool->addExtension(eventDispatcherHandleStorage, true);

    auto poolEventDispatcherHandleStorage =
        WRAPPED_POOL_EVENT_DISPATCHER(IVehicle)(&vehiclePool->getPoolEventDispatcher(), context);
    vehiclePool->addExtension(poolEventDispatcherHandleStorage, true);
}