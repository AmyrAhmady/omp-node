#include <utility>

#include "pickup_wrapper.hpp"
#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"
#include "../../converter/pickup.hpp"
#include "pickup_event_dispatcher_wrapper.hpp"

WRAP_BASIC(IPickupEventDispatcher)
WRAP_HANDLER_BASIC(PickupEventHandler, NodeJSPickupEventHandler)

WRAP_HANDLER(NodeJSPickupEventHandler, void, onPlayerPickUpPickup, 2, {
    args[0] = IPlayerToJS(player, context);
    args[1] = IPickupToJS(pickup, context);
}, return, return, IPlayer& player, IPickup& pickup)

WRAP_BASIC_CODE(IPickupEventDispatcher, addEventHandler, WRAP_ADD_EVENT_HANDLER(NodeJSPickupEventHandler))

WRAP_BASIC_CODE(IPickupEventDispatcher, hasEventHandler, WRAP_HAS_EVENT_HANDLER(NodeJSPickupEventHandler))

WRAP_BASIC_CODE(IPickupEventDispatcher, removeEventHandler, WRAP_REMOVE_EVENT_HANDLER(NodeJSPickupEventHandler))

WRAP_BASIC_CALL_RETURN(IPickupEventDispatcher, count, (size_t, UIntToJS))

v8::Local<v8::Value> WrapPickupEventDispatcher(IEventDispatcher<PickupEventHandler> *dispatcher,
                                                v8::Local<v8::Context> context) {

    v8::EscapableHandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(dispatcher, context, WRAPPED_METHODS(IPickupEventDispatcher));

    return hs.Escape(dispatcherHandle);
}