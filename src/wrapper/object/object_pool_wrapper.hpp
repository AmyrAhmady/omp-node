#pragma once
#include "Server/Components/Objects/objects.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapObjectPool(IObjectsComponent *objectPool, v8::Local<v8::Context> context);