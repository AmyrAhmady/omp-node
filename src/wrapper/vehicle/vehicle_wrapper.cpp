#include "vehicle_wrapper.hpp"
#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"
#include "../../converter/vehicle.hpp"
#include "../../converter/entity.hpp"
#include "../entity/entity_wrapper.hpp"

WRAP_BASIC(IVehicle)

WRAP_BASIC_CALL(IVehicle, setSpawnData, (const VehicleSpawnData&, FROM_JS_FN(VehicleSpawnData), data))

WRAP_BASIC_CALL_RETURN(IVehicle, getSpawnData, (const VehicleSpawnData&, TO_JS_FN(VehicleSpawnData)))

WRAP_BASIC_CALL_RETURN(IVehicle,
                       isStreamedInForPlayer,
                       (bool, BoolToJS),
                       (const IPlayer&, JSToEntityRef<IPlayer>, player))

WRAP_BASIC_CALL(IVehicle, streamInForPlayer, (IPlayer & , JSToEntityRef<IPlayer>, player))

WRAP_BASIC_CALL(IVehicle, streamOutForPlayer, (IPlayer & , JSToEntityRef<IPlayer>, player))

WRAP_BASIC_CALL(IVehicle, setColour, (int, JSToInt, col1), (int, JSToInt, col2))

WRAP_BASIC_CALL_RETURN(IVehicle, getColour, (VehicleColour, TO_JS_FN(VehicleColour)))

WRAP_BASIC_CALL(IVehicle, setHealth, (float, JSToFloat, Health))

WRAP_BASIC_CALL_RETURN(IVehicle, getHealth, (float, FloatToJS))

WRAP_BASIC_CALL_RETURN(IVehicle, streamedForPlayers, (const FlatPtrHashSetIPlayer&, TO_JS_FN(FlatPtrHashSetIPlayer)))

WRAP_BASIC_CALL_RETURN(IVehicle, getDriver, (IPlayer * , EntityToJS<IPlayer>))

WRAP_BASIC_CALL_RETURN(IVehicle, getPassengers, (const FlatPtrHashSetIPlayer&, TO_JS_FN(FlatPtrHashSetIPlayer)))

WRAP_BASIC_CALL(IVehicle, setPlate, (Impl::String, JSToString, plate))

WRAP_BASIC_CALL_RETURN(IVehicle, getPlate, (const StringView, StringViewToJS))

WRAP_BASIC_CALL(IVehicle,
                setDamageStatus,
                (int, JSToInt, PanelStatus),
                (int, JSToInt, DoorStatus),
                (uint8_t, JSToUInt<uint8_t>, LightStatus),
                (uint8_t, JSToUInt<uint8_t>, TyreStatus),
                (IPlayer * , JSToEntity<IPlayer>, vehicleUpdater, nullptr))

WRAP_BASIC_CODE(IVehicle, getDamageStatus, {
    ENTER_FUNCTION_CALLBACK(info);
    auto external = GetContextExternalPointer<IVehicle>(info);
    if (external == nullptr) {
        return;
    }

    int panel;
    int door;
    int light;
    int tyre;

    external->getDamageStatus(panel, door, light, tyre);

    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), 4);

    if (array.IsEmpty()) {
        info.GetReturnValue().Set(v8::Null(isolate));
        return;
    }

    array->Set(context, 0, IntToJS(panel, context)).Check();
    array->Set(context, 1, IntToJS(door, context)).Check();
    array->Set(context, 2, IntToJS(light, context)).Check();
    array->Set(context, 3, IntToJS(tyre, context)).Check();

    info.GetReturnValue().Set(array);
})

WRAP_BASIC_CALL(IVehicle, setPaintJob, (int, JSToInt, paintjob))

WRAP_BASIC_CALL_RETURN(IVehicle, getPaintJob, (int, IntToJS))

WRAP_BASIC_CALL(IVehicle, addComponent, (int, JSToInt, component))

WRAP_BASIC_CALL_RETURN(IVehicle, getComponentInSlot, (int, IntToJS), (int, JSToInt, slot))

WRAP_BASIC_CALL(IVehicle, removeComponent, (int, JSToInt, component))

WRAP_BASIC_CALL(IVehicle, putPlayer, (IPlayer & , JSToEntityRef<IPlayer>, player), (int, JSToInt, SeatID))

WRAP_BASIC_CALL(IVehicle, setZAngle, (float, JSToFloat, angle))

WRAP_BASIC_CALL_RETURN(IVehicle, getZAngle, (float, FloatToJS))

WRAP_BASIC_CALL(IVehicle, setParams, (const VehicleParams&, FROM_JS_FN(VehicleParams), params))

WRAP_BASIC_CALL(IVehicle,
                setParamsForPlayer,
                (IPlayer & , JSToEntityRef<IPlayer>, player),
                (const VehicleParams&, FROM_JS_FN(VehicleParams), params))

WRAP_BASIC_CALL_RETURN(IVehicle, getParams, (VehicleParams const&, TO_JS_FN(VehicleParams)))

WRAP_BASIC_CALL_RETURN(IVehicle, isDead, (bool, BoolToJS))

WRAP_BASIC_CALL(IVehicle, respawn)

WRAP_BASIC_CALL_RETURN(IVehicle, getRespawnDelay, (Seconds, TO_JS_FN(Seconds)))

WRAP_BASIC_CALL(IVehicle, setRespawnDelay, (Seconds, FROM_JS_FN(Seconds), delay))

WRAP_BASIC_CALL_RETURN(IVehicle, isRespawning, (bool, BoolToJS))

WRAP_BASIC_CALL(IVehicle, setInterior, (int, JSToInt, InteriorID))

WRAP_BASIC_CALL_RETURN(IVehicle, getInterior, (int, IntToJS))

WRAP_BASIC_CALL(IVehicle, attachTrailer, (IVehicle & , JSToEntityRef<IVehicle>, trailer))

WRAP_BASIC_CALL(IVehicle, detachTrailer)

WRAP_BASIC_CALL_RETURN(IVehicle, isTrailer, (bool, BoolToJS))

WRAP_BASIC_CALL_RETURN(IVehicle, getTrailer, (IVehicle * , EntityToJS<IVehicle>))

WRAP_BASIC_CALL_RETURN(IVehicle, getTower, (IVehicle * , EntityToJS<IVehicle>))

WRAP_BASIC_CALL(IVehicle, repair)

WRAP_BASIC_CALL(IVehicle, addCarriage, (IVehicle * , JSToEntity<IVehicle>, carriage), (int, JSToInt, pos))
WRAP_BASIC_CALL(IVehicle, updateCarriage, (Vector3, JSToVector<Vector3>, pos), (Vector3, JSToVector<Vector3>, veloc))
WRAP_BASIC_CALL_RETURN(IVehicle, getCarriages, (const VehicleCarriages&, TO_JS_FN(VehicleCarriages)))

WRAP_BASIC_CALL(IVehicle, setVelocity, (Vector3, JSToVector<Vector3>, velocity))

WRAP_BASIC_CALL_RETURN(IVehicle, getVelocity, (Vector3, VectorToJS<Vector3>))

WRAP_BASIC_CALL(IVehicle, setAngularVelocity, (Vector3, JSToVector<Vector3>, velocity))

WRAP_BASIC_CALL_RETURN(IVehicle, getAngularVelocity, (Vector3, VectorToJS<Vector3>))

WRAP_BASIC_CALL_RETURN(IVehicle, getModel, (int, IntToJS))

WRAP_BASIC_CALL_RETURN(IVehicle, getLandingGearState, (uint8_t, UIntToJS<uint8_t>))

WRAP_BASIC_CALL_RETURN(IVehicle, hasBeenOccupied, (bool, BoolToJS))

WRAP_BASIC_CALL_RETURN(IVehicle, getLastOccupiedTime, (const TimePoint&, TO_JS_FN(TimePoint)))

WRAP_BASIC_CALL_RETURN(IVehicle, getLastSpawnTime, (const TimePoint&, TO_JS_FN(TimePoint)))

WRAP_BASIC_CALL_RETURN(IVehicle, isOccupied, (bool, BoolToJS))

WRAP_BASIC_CALL(IVehicle, setSiren, (bool, JSToBool, status))

WRAP_BASIC_CALL_RETURN(IVehicle, getSirenState, (uint8_t, UIntToJS<uint8_t>))

WRAP_BASIC_CALL_RETURN(IVehicle, getHydraThrustAngle, (uint32_t, UIntToJS))

WRAP_BASIC_CALL_RETURN(IVehicle, getTrainSpeed, (float, FloatToJS));

WRAP_ENTITY_METHODS(IVehicle)

void WrapVehicle(IVehicle *vehicle, v8::Local<v8::Context> context) {
    auto vehicleHandle = InterfaceToObject(vehicle, context, WRAPPED_METHODS(IVehicle));

    vehicle->addExtension(new IHandleStorage(context->GetIsolate(), vehicleHandle), true);
}