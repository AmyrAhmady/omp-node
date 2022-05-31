#include "variable_component_wrapper.hpp"
#include "../../converter/types.hpp"
#include "variable_storage_base_wrapper.hpp"

WRAP_BASIC(IVariablesComponent)

WRAP_VARIABLE_STORAGE_BASE_METHODS(IVariablesComponent)

void WrapVariableComponent(IVariablesComponent *component, v8::Local<v8::Context> context) {
    auto coreHandle = InterfaceToObject(component, context, WRAPPED_METHODS(IVariablesComponent));

    component->addExtension(new IHandleStorage(context->GetIsolate(), coreHandle), true);
}
