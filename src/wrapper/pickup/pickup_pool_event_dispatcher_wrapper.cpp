#include <utility>

#include "pickup_wrapper.hpp"
#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/pickup.hpp"
#include "pickup_pool_event_dispatcher_wrapper.hpp"

WRAP_BASIC(IPickupPoolEventDispatcher)
WRAP_HANDLER_BASIC(PickupPoolEventHandler, NodeJSPickupPoolEventHandler)

WRAP_HANDLER(NodeJSPickupPoolEventHandler, void, onPoolEntryCreated, 1, {
    args[0] = GetHandleStorageExtension(&pickup)->get();
}, return, IPickup &pickup)

WRAP_HANDLER(NodeJSPickupPoolEventHandler, void, onPoolEntryDestroyed, 1, {
    args[0] = GetHandleStorageExtension(&pickup)->get();
}, return, IPickup &pickup)

WRAP_BASIC_CODE(IPickupPoolEventDispatcher, addEventHandler, WRAP_ADD_EVENT_HANDLER(NodeJSPickupPoolEventHandler))

WRAP_BASIC_CODE(IPickupPoolEventDispatcher, hasEventHandler, WRAP_HAS_EVENT_HANDLER(NodeJSPickupPoolEventHandler))

WRAP_BASIC_CODE(IPickupPoolEventDispatcher, removeEventHandler, WRAP_REMOVE_EVENT_HANDLER(NodeJSPickupPoolEventHandler))

WRAP_BASIC_CALL_RETURN(IPickupPoolEventDispatcher, count, (size_t, UIntToJS))

v8::Local<v8::Value> WrapPickupPoolEventDispatcher(IEventDispatcher<PickupPoolEventHandler> *dispatcher,
                                                   v8::Local<v8::Context> context) {

    v8::EscapableHandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(dispatcher, context, WRAPPED_METHODS(IPickupPoolEventDispatcher));

    return hs.Escape(dispatcherHandle);
}