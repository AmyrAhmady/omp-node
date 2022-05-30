#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/Checkpoints/checkpoints.hpp"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0xbc88a5b33555560e, CheckpointDataHandleStorage)

CheckpointDataHandleStorage *WrapCheckpointData(ICheckpointData &data,
                                                v8::Local<v8::Context> context) __attribute__((warn_unused_result));
