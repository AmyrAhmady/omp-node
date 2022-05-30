#pragma once
#include "Server/Components/Classes/classes.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapClassPool(IClassesComponent *playerClassPool, v8::Local<v8::Context> context);