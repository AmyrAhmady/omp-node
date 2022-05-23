#include "vehicle_wrapper.hpp"
#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"
#include "../../converter/vehicle.hpp"

WRAP_BASIC(IVehicle)

WRAP_BASIC_CALL(IVehicle, setSpawnData, JSToVehicleSpawnData(info[0], context))
WRAP_BASIC_CALL_RETURN(IVehicle, getSpawnData, VehicleSpawnDataToJS)
WRAP_BASIC_CALL_RETURN(IVehicle, isStreamedInForPlayer, BoolToJS, *JSToIPlayer(info[0], context))
WRAP_BASIC_CALL(IVehicle, streamInForPlayer, *JSToIPlayer(info[0], context))
WRAP_BASIC_CALL(IVehicle, streamOutForPlayer, *JSToIPlayer(info[0], context))
WRAP_BASIC_CALL(IVehicle, setColour, JSToInt(info[0], context), JSToInt(info[1], context))
WRAP_BASIC_CALL_RETURN(IVehicle, getColour, VehicleColourToJS)
WRAP_BASIC_CALL(IVehicle, setHealth, JSToFloat(info[0], context))
WRAP_BASIC_CALL_RETURN(IVehicle, getHealth, FloatToJS)
//WRAP_BASIC_CALL_RETURN(IVehicle, updateFromDriverSync, BoolToJS, const VehicleDriverSyncPacket &vehicleSync, JSToIPlayer(info[1], context))
//WRAP_BASIC_CALL_RETURN(IVehicle, updateFromPassengerSync, BoolToJS, const VehiclePassengerSyncPacket &passengerSync, JSToIPlayer(info[1], context))
//WRAP_BASIC_CALL_RETURN(IVehicle, updateFromUnoccupied, BoolToJS, const VehicleUnoccupiedSyncPacket &unoccupiedSync, JSToIPlayer(info[1], context))
//WRAP_BASIC_CALL_RETURN(IVehicle, updateFromTrailerSync, BoolToJS, const VehicleTrailerSyncPacket &unoccupiedSync, JSToIPlayer(info[1], context))
WRAP_BASIC_CALL_RETURN(IVehicle, streamedForPlayers, FlatPtrHashSetIPlayerToJS)
WRAP_BASIC_CALL_RETURN(IVehicle, getDriver, IPlayerToJS)
WRAP_BASIC_CALL_RETURN(IVehicle, getPassengers, FlatPtrHashSetIPlayerToJS)
WRAP_BASIC_CALL(IVehicle, setPlate, JSToString(info[0], context))
WRAP_BASIC_CALL_RETURN(IVehicle, getPlate, StringViewToJS)
WRAP_BASIC_CALL(IVehicle,
                setDamageStatus,
                JSToInt(info[0], context),
                JSToInt(info[1], context),
                JSToUInt(info[2], context),
                JSToUInt(info[3], context),
                JSToIPlayer(info[4], context, nullptr))
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

    array->Set(context, 0, IntToJS(panel, context));
    array->Set(context, 1, IntToJS(door, context));
    array->Set(context, 2, IntToJS(light, context));
    array->Set(context, 3, IntToJS(tyre, context));

    info.GetReturnValue().Set(array);
})
WRAP_BASIC_CALL(IVehicle, setPaintJob, JSToInt(info[0], context))
WRAP_BASIC_CALL_RETURN(IVehicle, getPaintJob, IntToJS)
WRAP_BASIC_CALL(IVehicle, addComponent, JSToInt(info[0], context))
WRAP_BASIC_CALL_RETURN(IVehicle, getComponentInSlot, IntToJS, JSToInt(info[0], context))
WRAP_BASIC_CALL(IVehicle, removeComponent, JSToInt(info[0], context))
WRAP_BASIC_CALL(IVehicle, putPlayer, *JSToIPlayer(info[0], context), JSToInt(info[1], context))
WRAP_BASIC_CALL(IVehicle, setZAngle, JSToFloat(info[0], context))
WRAP_BASIC_CALL_RETURN(IVehicle, getZAngle, FloatToJS)
WRAP_BASIC_CALL(IVehicle, setParams, JSToVehicleParams(info[0], context))
WRAP_BASIC_CALL(IVehicle, setParamsForPlayer, *JSToIPlayer(info[0], context), JSToVehicleParams(info[1], context))
WRAP_BASIC_CALL_RETURN(IVehicle, getParams, VehicleParamsToJS)
WRAP_BASIC_CALL_RETURN(IVehicle, isDead, BoolToJS)
WRAP_BASIC_CALL(IVehicle, respawn)
WRAP_BASIC_CALL_RETURN(IVehicle, getRespawnDelay, SecondsToJS)
WRAP_BASIC_CALL(IVehicle, setRespawnDelay, JSToSeconds(info[0], context))
WRAP_BASIC_CALL_RETURN(IVehicle, isRespawning, BoolToJS)
WRAP_BASIC_CALL(IVehicle, setInterior, JSToInt(info[0], context))
WRAP_BASIC_CALL_RETURN(IVehicle, getInterior, IntToJS)
WRAP_BASIC_CALL(IVehicle, attachTrailer, *JSToIVehicle(info[0], context))
WRAP_BASIC_CALL(IVehicle, detachTrailer)
WRAP_BASIC_CALL_RETURN(IVehicle, isTrailer, BoolToJS)
WRAP_BASIC_CALL_RETURN(IVehicle, getTrailer, IVehicleToJS)
WRAP_BASIC_CALL_RETURN(IVehicle, getTower, IVehicleToJS)
WRAP_BASIC_CALL(IVehicle, repair)
WRAP_BASIC_CALL(IVehicle, addCarriage, JSToIVehicle(info[0], context), JSToInt(info[0], context))
WRAP_BASIC_CALL(IVehicle, updateCarriage, JSToVector3(info[0], context), JSToVector3(info[1], context))
WRAP_BASIC_CALL_RETURN(IVehicle, getCarriages, CarriagesToJS)
WRAP_BASIC_CALL(IVehicle, setVelocity, JSToVector3(info[0], context))
WRAP_BASIC_CALL_RETURN(IVehicle, getVelocity, Vector3ToJS)
WRAP_BASIC_CALL(IVehicle, setAngularVelocity, JSToVector3(info[0], context))
WRAP_BASIC_CALL_RETURN(IVehicle, getAngularVelocity, Vector3ToJS)
WRAP_BASIC_CALL_RETURN(IVehicle, getModel, IntToJS)
WRAP_BASIC_CALL_RETURN(IVehicle, getLandingGearState, UIntToJS)
WRAP_BASIC_CALL_RETURN(IVehicle, hasBeenOccupied, BoolToJS)
WRAP_BASIC_CALL_RETURN(IVehicle, getLastOccupiedTime, TimePointToJS)
WRAP_BASIC_CALL_RETURN(IVehicle, getLastSpawnTime, TimePointToJS)
WRAP_BASIC_CALL_RETURN(IVehicle, isOccupied, BoolToJS)
WRAP_BASIC_CALL(IVehicle, setSiren, JSToBool(info[0], context))
WRAP_BASIC_CALL_RETURN(IVehicle, getSirenState, UIntToJS)
WRAP_BASIC_CALL_RETURN(IVehicle, getHydraThrustAngle, UIntToJS)
WRAP_BASIC_CALL_RETURN(IVehicle, getTrainSpeed, FloatToJS)

void WrapVehicle(IVehicle *vehicle, v8::Local<v8::Context> context) {
    auto vehicleHandle = InterfaceToObject(vehicle, context, WRAPPED_METHODS(IVehicle));

    vehicle->addExtension(new IHandleStorage(context->GetIsolate(), vehicleHandle), true);
}