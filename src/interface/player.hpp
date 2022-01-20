#include "sdk.hpp"
#include "v8.h"

v8::Local<v8::Object> IPlayerToObject(v8::Local<v8::Context> context, IPlayer *player);