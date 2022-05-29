#include "textlabel_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/vehicle.hpp"
#include "../../converter/entity.hpp"
#include "../../converter/textlabel.hpp"
#include "../entity/entity_wrapper.hpp"
#include "textlabel_base_wrapper.hpp"

WRAP_BASIC(ITextLabel)

WRAP_TEXTLABEL_BASE_METHODS(ITextLabel)

WRAP_BASIC_CALL_RETURN(ITextLabel, isStreamedInForPlayer, (bool, BoolToJS), (const IPlayer&, JSToEntityRef<IPlayer>, player))
WRAP_BASIC_CALL(ITextLabel, streamInForPlayer, (IPlayer&, JSToEntityRef<IPlayer>, player))
WRAP_BASIC_CALL(ITextLabel, streamOutForPlayer, (IPlayer&, JSToEntityRef<IPlayer>, player))

WRAP_ENTITY_METHODS(ITextLabel)

void WrapTextLabel(ITextLabel *textLabel, v8::Local<v8::Context> context) {
    auto textLabelHandle = InterfaceToObject(textLabel, context, WRAPPED_METHODS(ITextLabel));

    textLabel->addExtension(new IHandleStorage(context->GetIsolate(), textLabelHandle), true);
}