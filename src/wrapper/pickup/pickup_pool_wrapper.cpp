#include "../../logger.hpp"
#include "pickup_pool_wrapper.hpp"
#include "pickup_wrapper.hpp"
#include "pickup_event_dispatcher_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/entity.hpp"
#include "../entry_handler.hpp"
#include "../pool/read_only_pool_wrapper.hpp"
#include "../pool/pool_wrapper.hpp"

WRAP_BASIC(IPickupsComponent)

WRAP_BASIC_CALL_RETURN(IPickupsComponent,
                       create,
                       (IPickup * , EntityToJS<IPickup>),
                       (int, JSToInt, modelId),
                       (PickupType, JSToUInt<PickupType>, type),
                       (Vector3, JSToVector<Vector3>, pos),
                       (uint32_t, JSToUInt<uint32_t>, virtualWorld),
                       (bool, JSToBool, isStatic))

WRAP_LOCAL_EXT_HANDLE_STORAGE_GET(IPickupsComponent, getEventDispatcher, EventDispatcherHandleStorage)

WRAP_READ_ONLY_POOL_METHODS(IPickupsComponent, IPickup, EntityToJS<IPickup>)
WRAP_POOL_METHODS(IPickupsComponent, IPickup)

NodeJSEntryHandler<IPickup> *handler;

void WrapPickupPool(IPickupsComponent *pickupPool, v8::Local<v8::Context> context) {
    handler = new NodeJSEntryHandler<IPickup>(context, WrapPickup);
    pickupPool->getPoolEventDispatcher().addEventHandler(handler);
    pickupPool->addExtension(handler, true);

    auto pickupPoolHandle = InterfaceToObject(pickupPool, context, WRAPPED_METHODS(IPickupsComponent));
    pickupPool->addExtension(new IHandleStorage(context->GetIsolate(), pickupPoolHandle), true);

    auto eventDispatcherHandleStorage = WrapPickupEventDispatcher(&pickupPool->getEventDispatcher(), context);
    pickupPool->addExtension(eventDispatcherHandleStorage, true);

    auto poolEventDispatcherHandleStorage = WRAPPED_POOL_EVENT_DISPATCHER(IPickup)(&pickupPool->getPoolEventDispatcher(), context);
    pickupPool->addExtension(poolEventDispatcherHandleStorage, true);
}