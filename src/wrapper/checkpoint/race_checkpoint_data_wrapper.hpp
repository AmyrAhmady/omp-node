#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "Server/Components/Checkpoints/checkpoints.hpp"
#include "../utils.hpp"

CREATE_HANDLE_STORAGE_EXTENSION(0xfbab7428a54315d6, RaceCheckpointDataHandleStorage)

RaceCheckpointDataHandleStorage *WrapRaceCheckpointData(IRaceCheckpointData &data,
                                                        v8::Local<v8::Context> context) __attribute__((warn_unused_result));
