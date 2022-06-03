#include "textlabel_base_wrapper.hpp"
#include "../../converter/types.hpp"
#include "../../converter/entity.hpp"
#include "../../converter/textlabel.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR_INHERIT(ITextLabelBase, IEntity)

WRAP_BASIC_CALL(ITextLabelBase, setText, (Impl::String, FROM_JS_FN(String), text))
WRAP_BASIC_CALL_RETURN(ITextLabelBase, getText, (StringView, TO_JS_FN(StringView)))
WRAP_BASIC_CALL(ITextLabelBase, setColour, (Colour, FROM_JS_FN(Colour), colour))
WRAP_BASIC_CALL_RETURN(ITextLabelBase, getColour, (Colour, TO_JS_FN(Colour)))
WRAP_BASIC_CALL(ITextLabelBase, setDrawDistance, (float, JSToFloat, dist))
WRAP_BASIC_CALL_RETURN(ITextLabelBase, getDrawDistance, (float, FloatToJS))
WRAP_BASIC_CALL(ITextLabelBase, attachToPlayer, (IPlayer&, JSToEntityRef<IPlayer>, player), (Vector3, JSToVector<Vector3>, offset))
WRAP_BASIC_CALL(ITextLabelBase, attachToVehicle, (IVehicle&, JSToEntityRef<IVehicle>, vehicle), (Vector3, JSToVector<Vector3>, offset))
WRAP_BASIC_CALL_RETURN(ITextLabelBase, getAttachmentData, (const TextLabelAttachmentData&, TO_JS_FN(TextLabelAttachmentData)))
WRAP_BASIC_CALL(ITextLabelBase, detachFromPlayer, (Vector3, JSToVector<Vector3>, position))
WRAP_BASIC_CALL(ITextLabelBase, detachFromVehicle, (Vector3, JSToVector<Vector3>, position))
WRAP_BASIC_CALL(ITextLabelBase, setTestLOS, (bool, JSToBool, status))
WRAP_BASIC_CALL_RETURN(ITextLabelBase, getTestLOS, (bool, BoolToJS))
WRAP_BASIC_CALL(ITextLabelBase, setColourAndText, (Colour, FROM_JS_FN(Colour), colour), (Impl::String, FROM_JS_FN(String), text))
