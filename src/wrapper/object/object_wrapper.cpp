#include "object_wrapper.hpp"
#include "object_base_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/vehicle.hpp"
#include "../../converter/entity.hpp"
#include "../../converter/object.hpp"
#include "../entity/entity_wrapper.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR_INHERIT(IObject, IBaseObject)

WRAP_BASIC_CALL(IObject,
                attachToPlayer,
                (IPlayer & , JSToEntityRef<IPlayer>, player),
                (Vector3, JSToVector<Vector3>, offset),
                (Vector3, JSToVector<Vector3>, rotation))
WRAP_BASIC_CALL(IObject,
                attachToObject,
                (IObject & , JSToEntityRef<IObject>, object),
                (Vector3, JSToVector<Vector3>, offset),
                (Vector3, JSToVector<Vector3>, rotation),
                (bool, JSToBool, syncRotation))

void WrapObject(IObject *object, v8::Local<v8::Context> context) {
    auto objectHandle = CREATE_INSTANCE(IObject, object, context);

    object->addExtension(new IHandleStorage(context->GetIsolate(), objectHandle), true);
}
