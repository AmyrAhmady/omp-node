#include "textlabel_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/vehicle.hpp"
#include "../../converter/entity.hpp"
#include "../../converter/textlabel.hpp"
#include "../entity/entity_wrapper.hpp"
#include "textlabel_base_wrapper.hpp"

WRAP_BASIC(IPlayerTextLabel)

WRAP_TEXTLABEL_BASE_METHODS(IPlayerTextLabel)

WRAP_ENTITY_METHODS(IPlayerTextLabel)

void WrapPlayerTextLabel(ITextLabel *playerTextLabel, v8::Local<v8::Context> context) {
    auto textLabelHandle = InterfaceToObject(playerTextLabel, context, WRAPPED_METHODS(IPlayerTextLabel));

    playerTextLabel->addExtension(new IHandleStorage(context->GetIsolate(), textLabelHandle), true);
}