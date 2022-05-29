#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"
#include "race_checkpoint_data_wrapper.hpp"
#include "checkpoint_data_base_wrapper.hpp"

WRAP_BASIC(IRaceCheckpointData)

WRAP_CHECKPOINT_DATA_BASE_METHODS(IRaceCheckpointData)

WRAP_BASIC_CALL_RETURN(IRaceCheckpointData, getType, (RaceCheckpointType, EnumToJS<RaceCheckpointType>))
WRAP_BASIC_CALL(IRaceCheckpointData, setType, (RaceCheckpointType, JSToEnum<RaceCheckpointType>, type))
WRAP_BASIC_CALL_RETURN(IRaceCheckpointData, getNextPosition, (Vector3, VectorToJS<Vector3>))
WRAP_BASIC_CALL(IRaceCheckpointData, setNextPosition, (const Vector3&, JSToVector<Vector3>, nextPosition))

RaceCheckpointDataHandleStorage *WrapRaceCheckpointData(IRaceCheckpointData &data, v8::Local<v8::Context> context) {
    v8::HandleScope hs(context->GetIsolate());

    auto handle = InterfaceToObject(&data, context, WRAPPED_METHODS(IRaceCheckpointData));

    return new RaceCheckpointDataHandleStorage(context->GetIsolate(), handle);
}
