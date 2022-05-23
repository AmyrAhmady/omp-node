#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "../utils.hpp"
#include "../logger.hpp"

AnimationData JSToAnimationData(v8::Local<v8::Value> value, v8::Local<v8::Context> context);

v8::Local<v8::Object> AnimationDataToJS(const AnimationData &animationData, v8::Local<v8::Context> context);
v8::Local<v8::Object> PlayerAnimationDataToJS(const PlayerAnimationData &playerAnimationData,
                                              v8::Local<v8::Context> context);
