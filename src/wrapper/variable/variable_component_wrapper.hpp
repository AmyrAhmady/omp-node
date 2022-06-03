#pragma once
#include "sdk.hpp"
#include "v8.h"
#include "variable_component_wrapper.hpp"
#include "Server/Components/Variables/variables.hpp"
#include "../../logger.hpp"
#include "../utils.hpp"

WRAP_BASIC_DECLARE_WITH_CONSTRUCTOR_INHERIT(IVariablesComponent, IVariableStorageBase)

void WrapVariableComponent(IVariablesComponent *component, v8::Local<v8::Context> context);
