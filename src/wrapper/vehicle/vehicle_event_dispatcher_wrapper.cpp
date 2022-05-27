#include <utility>

#include "vehicle_wrapper.hpp"
#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"
#include "../../converter/vehicle.hpp"
#include "vehicle_event_dispatcher_wrapper.hpp"

WRAP_BASIC(IVehicleEventDispatcher)
WRAP_HANDLER_BASIC(VehicleEventHandler, NodeJSVehicleEventHandler)

WRAP_HANDLER(NodeJSVehicleEventHandler, void, onVehicleStreamIn, 2, {
    args[0] = IVehicleToJS(vehicle, context);
    args[1] = IPlayerToJS(player, context);
}, return, return, IVehicle &vehicle, IPlayer &player)

WRAP_HANDLER(NodeJSVehicleEventHandler, void, onVehicleStreamOut, 2, {
    args[0] = IVehicleToJS(vehicle, context);
    args[1] = IPlayerToJS(player, context);
}, return, return, IVehicle &vehicle, IPlayer &player)

WRAP_HANDLER(NodeJSVehicleEventHandler, void, onVehicleDeath, 2, {
    args[0] = IVehicleToJS(vehicle, context);
    args[1] = IPlayerToJS(player, context);
}, return, return, IVehicle &vehicle, IPlayer &player)

WRAP_HANDLER(NodeJSVehicleEventHandler, void, onPlayerEnterVehicle, 3, {
    args[0] = IPlayerToJS(player, context);
    args[1] = IVehicleToJS(vehicle, context);
    args[2] = BoolToJS(passenger, context);
}, return, return, IPlayer &player, IVehicle &vehicle, bool passenger)

WRAP_HANDLER(NodeJSVehicleEventHandler, void, onPlayerExitVehicle, 2, {
    args[0] = IPlayerToJS(player, context);
    args[1] = IVehicleToJS(vehicle, context);
}, return, return, IPlayer &player, IVehicle &vehicle)

WRAP_HANDLER(NodeJSVehicleEventHandler, void, onVehicleDamageStatusUpdate, 2, {
    args[0] = IVehicleToJS(vehicle, context);
    args[1] = IPlayerToJS(player, context);
}, return, return, IVehicle &vehicle, IPlayer &player)

WRAP_HANDLER(NodeJSVehicleEventHandler, bool, onVehiclePaintJob, 3, {
    args[0] = IPlayerToJS(player, context);
    args[1] = IVehicleToJS(vehicle, context);
    args[2] = IntToJS(paintJob, context);
}, return JSToBool(cbReturnedValue, context), return true, IPlayer &player, IVehicle &vehicle, int paintJob)

WRAP_HANDLER(NodeJSVehicleEventHandler, bool, onVehicleMod, 3, {
    args[0] = IPlayerToJS(player, context);
    args[1] = IVehicleToJS(vehicle, context);
    args[2] = IntToJS(component, context);
}, return JSToBool(cbReturnedValue, context), return true, IPlayer &player, IVehicle &vehicle, int component)

WRAP_HANDLER(NodeJSVehicleEventHandler, bool, onVehicleRespray, 4, {
    args[0] = IPlayerToJS(player, context);
    args[1] = IVehicleToJS(vehicle, context);
    args[2] = IntToJS(colour1, context);
    args[3] = IntToJS(colour2, context);
}, return JSToBool(cbReturnedValue, context), return true, IPlayer &player, IVehicle &vehicle, int colour1, int colour2)

WRAP_HANDLER(NodeJSVehicleEventHandler, void, onEnterExitModShop, 3, {
    args[0] = IPlayerToJS(player, context);
    args[1] = BoolToJS(enterexit, context);
    args[2] = IntToJS(interiorID, context);
}, return, return, IPlayer &player, bool enterexit, int interiorID)

WRAP_HANDLER(NodeJSVehicleEventHandler, void, onVehicleSpawn, 1, {
    args[0] = IVehicleToJS(vehicle, context);
}, return, return, IVehicle &vehicle)

WRAP_HANDLER(NodeJSVehicleEventHandler,
             bool,
             onUnoccupiedVehicleUpdate,
             3,
             {
                 args[0] = IVehicleToJS(vehicle, context);
                 args[1] = IPlayerToJS(player, context);
                 args[2] = UnoccupiedVehicleUpdateToJS(updateData, context);
             },
             return JSToBool(cbReturnedValue, context),
             return true,
             IVehicle &vehicle,
             IPlayer &player,
             UnoccupiedVehicleUpdate const updateData)

WRAP_HANDLER(NodeJSVehicleEventHandler, bool, onTrailerUpdate, 2, {
    args[0] = IPlayerToJS(player, context);
    args[1] = IVehicleToJS(trailer, context);
}, return JSToBool(cbReturnedValue, context), return true, IPlayer &player, IVehicle &trailer)

WRAP_HANDLER(NodeJSVehicleEventHandler, bool, onVehicleSirenStateChange, 3, {
    args[0] = IPlayerToJS(player, context);
    args[1] = IVehicleToJS(vehicle, context);
    args[2] = UIntToJS(sirenState, context);
}, return JSToBool(cbReturnedValue, context), return true, IPlayer &player, IVehicle &vehicle, uint8_t sirenState)

WRAP_BASIC_CODE(IVehicleEventDispatcher, addEventHandler, WRAP_ADD_EVENT_HANDLER(NodeJSVehicleEventHandler))

WRAP_BASIC_CODE(IVehicleEventDispatcher, hasEventHandler, WRAP_HAS_EVENT_HANDLER(NodeJSVehicleEventHandler))

WRAP_BASIC_CODE(IVehicleEventDispatcher, removeEventHandler, WRAP_REMOVE_EVENT_HANDLER(NodeJSVehicleEventHandler))

WRAP_BASIC_CALL_RETURN(IVehicleEventDispatcher, count, (size_t, UIntToJS))

v8::Local<v8::Value> WrapVehicleEventDispatcher(IEventDispatcher<VehicleEventHandler> *dispatcher,
                                                v8::Local<v8::Context> context) {

    v8::EscapableHandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(dispatcher, context, WRAPPED_METHODS(IVehicleEventDispatcher));

    return hs.Escape(dispatcherHandle);
}