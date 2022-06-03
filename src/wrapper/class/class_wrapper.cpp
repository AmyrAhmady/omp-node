#include "class_wrapper.hpp"
#include "../../converter/types.hpp"
#include "../../converter/class.hpp"
#include "../../converter/entity.hpp"
#include "../entity/entity_wrapper.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR_INHERIT(IClass, IIDProvider)

WRAP_BASIC_CALL_RETURN(IClass, getClass, (const PlayerClass&, PlayerClassToJS))
WRAP_BASIC_CALL(IClass, setClass, (const PlayerClass&, JSToPlayerClass, data))

void WrapClass(IClass *playerClass, v8::Local<v8::Context> context) {
    auto playerClassHandle = CREATE_INSTANCE(IClass, playerClass, context);

    playerClass->addExtension(new IHandleStorage(context->GetIsolate(), playerClassHandle), true);
}
