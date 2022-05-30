#include "class_wrapper.hpp"
#include "../../converter/types.hpp"
#include "../../converter/class.hpp"
#include "../../converter/entity.hpp"
#include "../entity/entity_wrapper.hpp"

WRAP_BASIC(IClass)

WRAP_BASIC_CALL_RETURN(IClass, getClass, (const PlayerClass&, PlayerClassToJS))
WRAP_BASIC_CALL(IClass, setClass, (const PlayerClass&, JSToPlayerClass, data))

WRAP_IID_PROVIDER_METHODS(IClass)

void WrapClass(IClass *playerClass, v8::Local<v8::Context> context) {
    auto playerClassHandle = InterfaceToObject(playerClass, context, WRAPPED_METHODS(IClass));

    playerClass->addExtension(new IHandleStorage(context->GetIsolate(), playerClassHandle), true);
}
