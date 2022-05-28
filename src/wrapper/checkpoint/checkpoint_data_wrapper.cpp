#include <utility>

#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"
#include "checkpoint_data_wrapper.hpp"
#include "checkpoint_data_base_wrapper.hpp"

WRAP_BASIC(ICheckpointData)

WRAP_CHECKPOINT_DATA_BASE_METHODS(ICheckpointData)

v8::Local<v8::Value> WrapCheckpointData(ICheckpointData &data,
                                                 v8::Local<v8::Context> context) {

    v8::EscapableHandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(&data, context, WRAPPED_METHODS(ICheckpointData));

    return hs.Escape(dispatcherHandle);
}