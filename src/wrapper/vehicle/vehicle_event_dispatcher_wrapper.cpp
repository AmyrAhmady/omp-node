#include <utility>

#include "vehicle_wrapper.hpp"
#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"
#include "../../converter/vehicle.hpp"
#include "vehicle_event_dispatcher_wrapper.hpp"

WRAP_BASIC(IVehicleEventDispatcher)
WRAP_HANDLER_BASIC(NodeJSEventHandler<VehicleEventHandler>, NodeJSVehicleEventHandler)

WRAP_HANDLER(NodeJSVehicleEventHandler, void, onVehicleStreamIn, 2, {
    args[0] = IVehicleToJS(vehicle, context);
    args[1] = IPlayerToJS(player, context);
}, return, IVehicle &vehicle, IPlayer &player)

WRAP_HANDLER(NodeJSVehicleEventHandler, void, onVehicleStreamOut, 2, {
    args[0] = IVehicleToJS(vehicle, context);
    args[1] = IPlayerToJS(player, context);
}, return, IVehicle &vehicle, IPlayer &player)

WRAP_HANDLER(NodeJSVehicleEventHandler, void, onVehicleDeath, 2, {
    args[0] = IVehicleToJS(vehicle, context);
    args[1] = IPlayerToJS(player, context);
}, return, IVehicle &vehicle, IPlayer &player)

WRAP_HANDLER(NodeJSVehicleEventHandler, void, onPlayerEnterVehicle, 3, {
    args[0] = IPlayerToJS(player, context);
    args[1] = IVehicleToJS(vehicle, context);
    args[2] = BoolToJS(passenger, context);
}, return, IPlayer &player, IVehicle &vehicle, bool passenger)

WRAP_HANDLER(NodeJSVehicleEventHandler, void, onPlayerExitVehicle, 2, {
    args[0] = IPlayerToJS(player, context);
    args[1] = IVehicleToJS(vehicle, context);
}, return, IPlayer &player, IVehicle &vehicle)

WRAP_HANDLER(NodeJSVehicleEventHandler, void, onVehicleDamageStatusUpdate, 2, {
    args[0] = IVehicleToJS(vehicle, context);
    args[1] = IPlayerToJS(player, context);
}, return, IVehicle &vehicle, IPlayer &player)

WRAP_HANDLER(NodeJSVehicleEventHandler, bool, onVehiclePaintJob, 3, {
    args[0] = IPlayerToJS(player, context);
    args[1] = IVehicleToJS(vehicle, context);
    args[2] = IntToJS(paintJob, context);
}, return JSToBool(cbReturnedValue, context), IPlayer &player, IVehicle &vehicle, int paintJob)

WRAP_HANDLER(NodeJSVehicleEventHandler, bool, onVehicleMod, 3, {
    args[0] = IPlayerToJS(player, context);
    args[1] = IVehicleToJS(vehicle, context);
    args[2] = IntToJS(component, context);
}, return JSToBool(cbReturnedValue, context), IPlayer &player, IVehicle &vehicle, int component)

WRAP_HANDLER(NodeJSVehicleEventHandler, bool, onVehicleRespray, 4, {
    args[0] = IPlayerToJS(player, context);
    args[1] = IVehicleToJS(vehicle, context);
    args[2] = IntToJS(colour1, context);
    args[3] = IntToJS(colour2, context);
}, return JSToBool(cbReturnedValue, context), IPlayer &player, IVehicle &vehicle, int colour1, int colour2)

WRAP_HANDLER(NodeJSVehicleEventHandler, void, onEnterExitModShop, 3, {
    args[0] = IPlayerToJS(player, context);
    args[1] = BoolToJS(enterexit, context);
    args[2] = IntToJS(interiorID, context);
}, return, IPlayer &player, bool enterexit, int interiorID)

WRAP_HANDLER(NodeJSVehicleEventHandler, void, onVehicleSpawn, 1, {
    args[0] = IVehicleToJS(vehicle, context);
}, return, IVehicle &vehicle)

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
             IVehicle &vehicle,
             IPlayer &player,
             UnoccupiedVehicleUpdate const updateData)

WRAP_HANDLER(NodeJSVehicleEventHandler, bool, onTrailerUpdate, 2, {
    args[0] = IPlayerToJS(player, context);
    args[1] = IVehicleToJS(trailer, context);
}, return JSToBool(cbReturnedValue, context), IPlayer &player, IVehicle &trailer)

WRAP_HANDLER(NodeJSVehicleEventHandler, bool, onVehicleSirenStateChange, 3, {
    args[0] = IPlayerToJS(player, context);
    args[1] = IVehicleToJS(vehicle, context);
    args[2] = UIntToJS(sirenState, context);
}, return JSToBool(cbReturnedValue, context), IPlayer &player, IVehicle &vehicle, uint8_t sirenState)

WRAP_BASIC_CODE(IVehicleEventDispatcher, addEventHandler, {
    ENTER_FUNCTION_CALLBACK(info)

    auto dispatcher = GetContextExternalPointer<IEventDispatcher<VehicleEventHandler>>(info);

    auto event = JSToString(info[0], context);
    auto handler = info[1].As<v8::Function>();
    auto priority = JSToEnum(info[2], context, EventPriority_Default);

    if (!handler->IsFunction()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A function is required").ToLocalChecked()));
        return;
    }

    auto handlerObjGenerator = WRAPPED_HANDLER(NodeJSVehicleEventHandler, event);

    if (handlerObjGenerator == nullptr) {
        info.GetReturnValue().Set(false);
        return;
    }

    auto handlerObj = handlerObjGenerator(event, handler);

    auto result = dispatcher->addEventHandler(handlerObj, priority);

    if (result) {
        WRAPPED_HANDLERS(NodeJSVehicleEventHandler).emplace(handlerObj);
    } else {
        delete handlerObj;
    }

    info.GetReturnValue().Set(result);

})

WRAP_BASIC_CODE(IVehicleEventDispatcher, hasEventHandler, {
    ENTER_FUNCTION_CALLBACK(info)

    auto dispatcher = GetContextExternalPointer<IEventDispatcher<VehicleEventHandler>>(info);

    auto event = JSToString(info[0], context);
    auto handler = info[1].As<v8::Function>();
    std::underlying_type_t<EventPriority> priority = JSToEnum<EventPriority>(info[2], context);

    if (!handler->IsFunction()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A function is required").ToLocalChecked()));
        return;
    }

    for (auto handlerObj: WRAPPED_HANDLERS(NodeJSVehicleEventHandler)) {
        if (handlerObj->getEvent() == event && handlerObj->getHandler() == handler) {
            auto result = dispatcher->hasEventHandler(handlerObj, priority);

            info.GetReturnValue().Set(result);

            return;
        }
    }

    info.GetReturnValue().Set(false);
})

WRAP_BASIC_CODE(IVehicleEventDispatcher, removeEventHandler, {
    ENTER_FUNCTION_CALLBACK(info)

    auto dispatcher = GetContextExternalPointer<IEventDispatcher<VehicleEventHandler>>(info);

    auto event = JSToString(info[0], context);
    auto handler = info[1].As<v8::Function>();

    if (!handler->IsFunction()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A function is required").ToLocalChecked()));
        return;
    }

    for (auto handlerObj: WRAPPED_HANDLERS(NodeJSVehicleEventHandler)) {
        if (handlerObj->getEvent() == event && handlerObj->getHandler() == handler) {
            auto result = dispatcher->removeEventHandler(handlerObj);

            info.GetReturnValue().Set(result);

            if (result) {
                WRAPPED_HANDLERS(NodeJSVehicleEventHandler).erase(handlerObj);
            }

            return;
        }
    }

    info.GetReturnValue().Set(false);
})

WRAP_BASIC_CALL_RETURN(IVehicleEventDispatcher, count, (size_t, UIntToJS))

v8::Local<v8::Value> WrapVehicleEventDispatcher(IEventDispatcher<VehicleEventHandler> *dispatcher,
                                                v8::Local<v8::Context> context) {

    v8::EscapableHandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(dispatcher, context, WRAPPED_METHODS(IVehicleEventDispatcher));

    return hs.Escape(dispatcherHandle);
}