#include "../../logger.hpp"
#include "player_checkpoint_data_wrapper.hpp"
#include "checkpoint_data_wrapper.hpp"
#include "race_checkpoint_data_wrapper.hpp"
#include "../../converter/entity.hpp"

WRAP_BASIC(IPlayerCheckpointData)

WRAP_BASIC_CODE(IPlayerCheckpointData, getCheckpoint, {
    ENTER_FUNCTION_CALLBACK(info)
    auto extensible = GetClosestExtensiblePointer<IPlayer>(info);
    if (extensible == nullptr) {
        return;
    }
    auto storageExtension = queryExtension<CheckpointDataHandleStorage>(extensible);
    auto handle = storageExtension->get();
    info.GetReturnValue().Set(handle);
})

WRAP_BASIC_CODE(IPlayerCheckpointData, getRaceCheckpoint, {
    ENTER_FUNCTION_CALLBACK(info)
    auto extensible = GetClosestExtensiblePointer<IPlayer>(info);
    if (extensible == nullptr) {
        return;
    }
    auto storageExtension = queryExtension<RaceCheckpointDataHandleStorage>(extensible);
    auto handle = storageExtension->get();
    info.GetReturnValue().Set(handle);
})

std::vector<IExtension *> WrapPlayerCheckpointData(IPlayer *player,
                                                   IPlayerCheckpointData *playerCheckpointData,
                                                   v8::Local<v8::Context> context) {

    std::vector<IExtension *> handleStorages;

    auto objectPoolHandle =
        InterfaceToObject(playerCheckpointData, context, WRAPPED_METHODS(IPlayerCheckpointData), player);
    handleStorages.push_back(new PlayerCheckpointDataHandleStorage(context->GetIsolate(), objectPoolHandle));

    auto checkpointDataHandleStorage = WrapCheckpointData(playerCheckpointData->getCheckpoint(), context);
    handleStorages.push_back(checkpointDataHandleStorage);

    auto raceCheckpointDataHandleStorage = WrapRaceCheckpointData(playerCheckpointData->getRaceCheckpoint(), context);
    handleStorages.push_back(raceCheckpointDataHandleStorage);

    return handleStorages;
}