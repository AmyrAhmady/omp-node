#include "../../logger.hpp"
#include "player_vehicle_data_wrapper.hpp"
#include "../../converter/entity.hpp"

WRAP_BASIC(IPlayerVehicleData)

WRAP_BASIC_CALL_RETURN(IPlayerVehicleData, getVehicle, (IVehicle * , EntityToJS<IVehicle>))
WRAP_BASIC_CALL_RETURN(IPlayerVehicleData, getSeat, (int, IntToJS))
WRAP_BASIC_CALL_RETURN(IPlayerVehicleData, isInModShop, (bool, BoolToJS))

std::vector<IExtension *> WrapPlayerVehicleData(IPlayer *player,
                                                    IPlayerVehicleData *playerVehicleData,
                                                    v8::Local<v8::Context> context) {

    std::vector<IExtension *> handleStorages;

    auto objectPoolHandle = InterfaceToObject(playerVehicleData, context, WRAPPED_METHODS(IPlayerVehicleData), player);
    handleStorages.push_back(new PlayerVehicleDataHandleStorage(context->GetIsolate(), objectPoolHandle));

    return handleStorages;
}
