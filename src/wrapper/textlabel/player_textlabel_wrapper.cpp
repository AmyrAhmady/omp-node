#include "player_textlabel_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/vehicle.hpp"
#include "../../converter/entity.hpp"
#include "../../converter/textlabel.hpp"
#include "../entity/entity_wrapper.hpp"
#include "textlabel_base_wrapper.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR_INHERIT(IPlayerTextLabel, ITextLabelBase)

void WrapPlayerTextLabel(IPlayerTextLabel *playerTextLabel, v8::Local<v8::Context> context) {
    auto textLabelHandle = CREATE_INSTANCE(IPlayerTextLabel, playerTextLabel, context);

    playerTextLabel->addExtension(new IHandleStorage(context->GetIsolate(), textLabelHandle), true);
}