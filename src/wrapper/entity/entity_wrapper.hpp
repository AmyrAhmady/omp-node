#pragma once

#define WRAP_ENTITY_METHODS(Type) \
    WRAP_BASIC_CALL_RETURN(Type, getID, (int, IntToJS)) \
    WRAP_BASIC_CALL_RETURN(Type, getPosition, (Vector3, VectorToJS<Vector3>)) \
    WRAP_BASIC_CALL(Type, setPosition, (Vector3, JSToVector<Vector3>, position)) \
    WRAP_BASIC_CALL_RETURN(Type, getRotation, (GTAQuat, GTAQuatToJS)) \
    WRAP_BASIC_CALL(Type, setRotation, (GTAQuat, JSToGTAQuat, rotation)) \
    WRAP_BASIC_CALL_RETURN(Type, getVirtualWorld, (int, IntToJS)) \
    WRAP_BASIC_CALL(Type, setVirtualWorld, (int, JSToInt, vw))