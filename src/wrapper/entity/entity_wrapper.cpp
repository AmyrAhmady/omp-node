#include "entity_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR_INHERIT(IEntity, IIDProvider)

WRAP_BASIC_CALL_RETURN(IEntity, getPosition, (Vector3, VectorToJS<Vector3>))
WRAP_BASIC_CALL(IEntity, setPosition, (Vector3, JSToVector<Vector3>, position))
WRAP_BASIC_CALL_RETURN(IEntity, getRotation, (GTAQuat, GTAQuatToJS))
WRAP_BASIC_CALL(IEntity, setRotation, (GTAQuat, JSToGTAQuat, rotation))
WRAP_BASIC_CALL_RETURN(IEntity, getVirtualWorld, (int, IntToJS))
WRAP_BASIC_CALL(IEntity, setVirtualWorld, (int, JSToInt, vw))
