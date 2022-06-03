#include "variable_component_wrapper.hpp"
#include "../../converter/types.hpp"
#include "variable_storage_base_wrapper.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR_INHERIT(IVariablesComponent, IVariableStorageBase)

void WrapVariableComponent(IVariablesComponent *component, v8::Local<v8::Context> context) {
    auto coreHandle = CREATE_INSTANCE(IVariablesComponent, component, context);

    component->addExtension(new IHandleStorage(context->GetIsolate(), coreHandle), true);
}
