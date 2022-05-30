#pragma once

#define WRAP_TEXT_DRAW_BASE_METHODS(Type) \
    WRAP_BASIC_CALL_RETURN(Type, getPosition, (Vector2, VectorToJS<Vector2>)) \
    WRAP_BASIC_CALL_RETURN(Type, setPosition, (ITextDrawBase&, EntityToJS<ITextDrawBase>), (Vector2, JSToVector<Vector2>, position)) \
    WRAP_BASIC_CALL(Type, setText, (Impl::String, FROM_JS_FN(String), text)) \
    WRAP_BASIC_CALL_RETURN(Type, getText, (StringView, TO_JS_FN(StringView))) \
    WRAP_BASIC_CALL_RETURN(Type, setLetterSize, (ITextDrawBase&, EntityToJS<ITextDrawBase>), (Vector2, JSToVector<Vector2>, size)) \
    WRAP_BASIC_CALL_RETURN(Type, getLetterSize, (Vector2, VectorToJS<Vector2>)) \
    WRAP_BASIC_CALL_RETURN(Type, setTextSize, (ITextDrawBase&, EntityToJS<ITextDrawBase>), (Vector2, JSToVector<Vector2>, size)) \
    WRAP_BASIC_CALL_RETURN(Type, getTextSize, (Vector2, VectorToJS<Vector2>)) \
    WRAP_BASIC_CALL_RETURN(Type, setAlignment, (ITextDrawBase&, EntityToJS<ITextDrawBase>), (TextDrawAlignmentTypes, JSToEnum<TextDrawAlignmentTypes>, alignment)) \
    WRAP_BASIC_CALL_RETURN(Type, getAlignment, (TextDrawAlignmentTypes, EnumToJS<TextDrawAlignmentTypes>)) \
    WRAP_BASIC_CALL_RETURN(Type, setColour, (ITextDrawBase&, EntityToJS<ITextDrawBase>), (Colour, FROM_JS_FN(Colour), colour)) \
    WRAP_BASIC_CALL_RETURN(Type, getLetterColour, (Colour, TO_JS_FN(Colour))) \
    WRAP_BASIC_CALL_RETURN(Type, useBox, (ITextDrawBase&, EntityToJS<ITextDrawBase>), (bool, JSToBool, use)) \
    WRAP_BASIC_CALL_RETURN(Type, hasBox, (bool, BoolToJS)) \
    WRAP_BASIC_CALL_RETURN(Type, setBoxColour, (ITextDrawBase&, EntityToJS<ITextDrawBase>), (Colour, FROM_JS_FN(Colour), colour)) \
    WRAP_BASIC_CALL_RETURN(Type, getBoxColour, (Colour, TO_JS_FN(Colour))) \
    WRAP_BASIC_CALL_RETURN(Type, setShadow, (ITextDrawBase&, EntityToJS<ITextDrawBase>), (int, JSToInt<int>, shadow)) \
    WRAP_BASIC_CALL_RETURN(Type, getShadow, (int, IntToJS<int>)) \
    WRAP_BASIC_CALL_RETURN(Type, setOutline, (ITextDrawBase&, EntityToJS<ITextDrawBase>), (int, JSToInt<int>, outline)) \
    WRAP_BASIC_CALL_RETURN(Type, getOutline, (int, IntToJS<int>)) \
    WRAP_BASIC_CALL_RETURN(Type, setBackgroundColour, (ITextDrawBase&, EntityToJS<ITextDrawBase>), (Colour, FROM_JS_FN(Colour), colour)) \
    WRAP_BASIC_CALL_RETURN(Type, getBackgroundColour, (Colour, TO_JS_FN(Colour))) \
    WRAP_BASIC_CALL_RETURN(Type, setStyle, (ITextDrawBase&, EntityToJS<ITextDrawBase>), (TextDrawStyle, JSToEnum<TextDrawStyle>, style)) \
    WRAP_BASIC_CALL_RETURN(Type, getStyle, (TextDrawStyle, EnumToJS<TextDrawStyle>)) \
    WRAP_BASIC_CALL_RETURN(Type, setProportional, (ITextDrawBase&, EntityToJS<ITextDrawBase>), (bool, JSToBool, proportional)) \
    WRAP_BASIC_CALL_RETURN(Type, isProportional, (bool, BoolToJS)) \
    WRAP_BASIC_CALL_RETURN(Type, setSelectable, (ITextDrawBase&, EntityToJS<ITextDrawBase>), (bool, JSToBool, selectable)) \
    WRAP_BASIC_CALL_RETURN(Type, isSelectable, (bool, BoolToJS)) \
    WRAP_BASIC_CALL_RETURN(Type, setPreviewModel, (ITextDrawBase&, EntityToJS<ITextDrawBase>), (int, JSToInt<int>, model)) \
    WRAP_BASIC_CALL_RETURN(Type, getPreviewModel, (int, IntToJS<int>)) \
    WRAP_BASIC_CALL_RETURN(Type, setPreviewRotation, (ITextDrawBase&, EntityToJS<ITextDrawBase>), (GTAQuat, FROM_JS_FN(GTAQuat), rotation)) \
    WRAP_BASIC_CALL_RETURN(Type, getPreviewRotation, (GTAQuat, TO_JS_FN(GTAQuat))) \
    WRAP_BASIC_CALL_RETURN(Type, setPreviewVehicleColour, (ITextDrawBase&, EntityToJS<ITextDrawBase>), (int, JSToInt<int>, colour1), (int, JSToInt<int>, colour2)) \
    WRAP_BASIC_CALL_RETURN(Type, getPreviewVehicleColour, (VehicleColour, TO_JS_FN(VehicleColour))) \
    WRAP_BASIC_CALL_RETURN(Type, setPreviewZoom, (ITextDrawBase&, EntityToJS<ITextDrawBase>), (float, JSToFloat, zoom)) \
    WRAP_BASIC_CALL_RETURN(Type, getPreviewZoom, (float, FloatToJS)) \
    WRAP_BASIC_CALL(Type, restream)
