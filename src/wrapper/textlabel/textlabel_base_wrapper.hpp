#pragma once

#define WRAP_TEXTLABEL_BASE_METHODS(Type) \
    WRAP_BASIC_CALL(Type, setText, (Impl::String, FROM_JS_FN(String), text)) \
    WRAP_BASIC_CALL_RETURN(Type, getText, (StringView, TO_JS_FN(StringView))) \
    WRAP_BASIC_CALL(Type, setColour, (Colour, FROM_JS_FN(Colour), colour)) \
    WRAP_BASIC_CALL_RETURN(Type, getColour, (Colour, TO_JS_FN(Colour))) \
    WRAP_BASIC_CALL(Type, setDrawDistance, (float, JSToFloat, dist)) \
    WRAP_BASIC_CALL_RETURN(Type, getDrawDistance, (float, FloatToJS)) \
    WRAP_BASIC_CALL(Type, attachToPlayer, (IPlayer&, JSToEntityRef<IPlayer>, player), (Vector3, JSToVector<Vector3>, offset)) \
    WRAP_BASIC_CALL(Type, attachToVehicle, (IVehicle&, JSToEntityRef<IVehicle>, vehicle), (Vector3, JSToVector<Vector3>, offset)) \
    WRAP_BASIC_CALL_RETURN(Type, getAttachmentData, (const TextLabelAttachmentData&, TO_JS_FN(TextLabelAttachmentData))) \
    WRAP_BASIC_CALL(Type, detachFromPlayer, (Vector3, JSToVector<Vector3>, position)) \
    WRAP_BASIC_CALL(Type, detachFromVehicle, (Vector3, JSToVector<Vector3>, position)) \
    WRAP_BASIC_CALL(Type, setTestLOS, (bool, JSToBool, status)) \
    WRAP_BASIC_CALL_RETURN(Type, getTestLOS, (bool, BoolToJS)) \
    WRAP_BASIC_CALL(Type, setColourAndText, (Colour, FROM_JS_FN(Colour), colour), (Impl::String, FROM_JS_FN(String), text))