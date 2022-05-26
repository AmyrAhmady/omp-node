#include "../../logger.hpp"
#include "pickup_pool_wrapper.hpp"
#include "pickup_wrapper.hpp"
#include "pickup_event_dispatcher_wrapper.hpp"
#include "pickup_pool_event_dispatcher_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/pickup.hpp"
#include "../entry_handler.hpp"

WRAP_BASIC(IPickupsComponent)

WRAP_BASIC_CALL_RETURN(IPickupsComponent,
                       create,
                       (IPickup* , TO_JS_FN(IPickup)),
                       (int, JSToInt, modelId),
                       (PickupType, JSToUInt<PickupType>, type),
                       (Vector3, JSToVector<Vector3>, pos),
                       (uint32_t, JSToUInt<uint32_t>, virtualWorld),
                       (bool, JSToBool, isStatic))

WRAP_BASIC_CODE(IPickupsComponent, getEventDispatcher, {
    ENTER_FUNCTION_CALLBACK(info)
    auto pool = GetContextExternalPointer<IPickupsComponent>(info);
    auto dispatcher = &pool->getEventDispatcher();
    auto dispatcherHandle = WrapPickupEventDispatcher(dispatcher, context);
    info.GetReturnValue().Set(dispatcherHandle);
})
WRAP_BASIC_CODE(IPickupsComponent, getPoolEventDispatcher, {
    ENTER_FUNCTION_CALLBACK(info)
    auto pool = GetContextExternalPointer<IPickupsComponent>(info);
    auto dispatcher = &pool->getPoolEventDispatcher();
    auto dispatcherHandle = WrapPickupPoolEventDispatcher(dispatcher, context);
    info.GetReturnValue().Set(dispatcherHandle);
})

NodeJSEntryHandler<IPickup> *handler;

void WrapPickupPool(IPickupsComponent *pickupPool, v8::Local<v8::Context> context) {
    handler = new NodeJSEntryHandler<IPickup>(context, WrapPickup); // todo: store somewhere to delete later

    pickupPool->getPoolEventDispatcher().addEventHandler(handler);

    auto pickupPoolHandle = InterfaceToObject(pickupPool, context, WRAPPED_METHODS(IPickupsComponent));

    pickupPool->addExtension(new IHandleStorage(context->GetIsolate(), pickupPoolHandle), true);
}