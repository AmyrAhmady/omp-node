#include "object_wrapper.hpp"
#include "object_base_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/vehicle.hpp"
#include "../../converter/entity.hpp"
#include "../../converter/object.hpp"
#include "../entity/entity_wrapper.hpp"

WRAP_BASIC(IPlayerObject)

WRAP_OBJECT_BASE_METHODS(IPlayerObject)

WRAP_BASIC_CALL(IPlayerObject,
                attachToObject,
                (IPlayerObject & , JSToEntityRef<IPlayerObject>, object),
                (Vector3, JSToVector<Vector3>, offset),
                (Vector3, JSToVector<Vector3>, rotation))

WRAP_ENTITY_METHODS(IPlayerObject)

void WrapPlayerObject(IPlayerObject *playerObject, v8::Local<v8::Context> context) {
    auto objectHandle = InterfaceToObject(playerObject, context, WRAPPED_METHODS(IPlayerObject));

    playerObject->addExtension(new IHandleStorage(context->GetIsolate(), objectHandle), true);
}
