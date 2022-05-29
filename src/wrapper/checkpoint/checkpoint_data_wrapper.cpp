#include <utility>

#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"
#include "checkpoint_data_wrapper.hpp"
#include "checkpoint_data_base_wrapper.hpp"

WRAP_BASIC(ICheckpointData)

WRAP_CHECKPOINT_DATA_BASE_METHODS(ICheckpointData)

CheckpointDataHandleStorage *WrapCheckpointData(ICheckpointData &data, v8::Local<v8::Context> context) {
    v8::HandleScope hs(context->GetIsolate());

    auto handle = InterfaceToObject(&data, context, WRAPPED_METHODS(ICheckpointData));

    return new CheckpointDataHandleStorage(context->GetIsolate(), handle);
}
