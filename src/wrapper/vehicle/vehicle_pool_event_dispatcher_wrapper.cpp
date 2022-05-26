#include <utility>

#include "vehicle_wrapper.hpp"
#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/vehicle.hpp"
#include "vehicle_pool_event_dispatcher_wrapper.hpp"

WRAP_BASIC(IVehiclePoolEventDispatcher)
WRAP_HANDLER_BASIC(VehiclePoolEventHandler, NodeJSVehiclePoolEventHandler)

WRAP_HANDLER(NodeJSVehiclePoolEventHandler, void, onPoolEntryCreated, 1, {
    args[0] = GetHandleStorageExtension(&vehicle)->get();
}, return, IVehicle &vehicle)

WRAP_HANDLER(NodeJSVehiclePoolEventHandler, void, onPoolEntryDestroyed, 1, {
    args[0] = GetHandleStorageExtension(&vehicle)->get();
}, return, IVehicle &vehicle)

WRAP_BASIC_CODE(IVehiclePoolEventDispatcher, addEventHandler, WRAP_ADD_EVENT_HANDLER(NodeJSVehiclePoolEventHandler))

WRAP_BASIC_CODE(IVehiclePoolEventDispatcher, hasEventHandler, WRAP_HAS_EVENT_HANDLER(NodeJSVehiclePoolEventHandler))

WRAP_BASIC_CODE(IVehiclePoolEventDispatcher, removeEventHandler, WRAP_REMOVE_EVENT_HANDLER(NodeJSVehiclePoolEventHandler))

WRAP_BASIC_CALL_RETURN(IVehiclePoolEventDispatcher, count, (size_t, UIntToJS))

v8::Local<v8::Value> WrapVehiclePoolEventDispatcher(IEventDispatcher<VehiclePoolEventHandler> *dispatcher,
                                                   v8::Local<v8::Context> context) {

    v8::EscapableHandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(dispatcher, context, WRAPPED_METHODS(IVehiclePoolEventDispatcher));

    return hs.Escape(dispatcherHandle);
}