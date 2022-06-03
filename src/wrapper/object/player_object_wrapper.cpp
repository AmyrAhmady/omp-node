#include "object_wrapper.hpp"
#include "object_base_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/vehicle.hpp"
#include "../../converter/entity.hpp"
#include "../../converter/object.hpp"
#include "../entity/entity_wrapper.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR_INHERIT(IPlayerObject, IBaseObject)

WRAP_BASIC_CALL(IPlayerObject,
                attachToObject,
                (IPlayerObject & , JSToEntityRef<IPlayerObject>, object),
                (Vector3, JSToVector<Vector3>, offset),
                (Vector3, JSToVector<Vector3>, rotation))

void WrapPlayerObject(IPlayerObject *playerObject, v8::Local<v8::Context> context) {
    auto objectHandle = CREATE_INSTANCE(IPlayerObject, playerObject, context);

    playerObject->addExtension(new IHandleStorage(context->GetIsolate(), objectHandle), true);
}
