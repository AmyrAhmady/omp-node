#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "variable_component_wrapper.hpp"
#include "Server/Components/Variables/variables.hpp"
#include "../../logger.hpp"
#include "../utils.hpp"

void WrapVariableComponent(IVariablesComponent *component, v8::Local<v8::Context> context);
