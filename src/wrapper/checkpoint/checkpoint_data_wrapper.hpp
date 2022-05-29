#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/Checkpoints/checkpoints.hpp"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0x21311f10b0f2e5a6, CheckpointDataHandleStorage)

CheckpointDataHandleStorage *WrapCheckpointData(ICheckpointData &data,
                                                v8::Local<v8::Context> context) __attribute__((warn_unused_result));
