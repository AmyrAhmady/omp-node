#pragma once

#define WRAP_CHECKPOINT_DATA_BASE_METHODS(InterfaceType) \
    WRAP_BASIC_CALL_RETURN(InterfaceType, getPosition, (Vector3, VectorToJS<Vector3>)) \
    WRAP_BASIC_CALL(InterfaceType, setPosition, (const Vector3&, JSToVector<Vector3>, position)) \
    WRAP_BASIC_CALL_RETURN(InterfaceType, getRadius, (float, FloatToJS)) \
    WRAP_BASIC_CALL(InterfaceType, setRadius, (float, JSToFloat, radius)) \
    WRAP_BASIC_CALL_RETURN(InterfaceType, isPlayerInside, (bool, BoolToJS)) \
    WRAP_BASIC_CALL(InterfaceType, setPlayerInside, (bool, JSToBool, inside)) \
    WRAP_BASIC_CALL(InterfaceType, enable) \
    WRAP_BASIC_CALL(InterfaceType, disable) \
    WRAP_BASIC_CALL_RETURN(InterfaceType, isEnabled, (bool, BoolToJS)) \
