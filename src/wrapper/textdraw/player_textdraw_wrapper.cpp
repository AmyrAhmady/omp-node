#include "textdraw_wrapper.hpp"
#include "textdraw_base_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/vehicle.hpp"
#include "../../converter/entity.hpp"
#include "../entity/entity_wrapper.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR_INHERIT(IPlayerTextDraw, ITextDrawBase)

WRAP_BASIC_CALL(IPlayerTextDraw, show)
WRAP_BASIC_CALL(IPlayerTextDraw, hide)
WRAP_BASIC_CALL_RETURN(IPlayerTextDraw, isShown, (bool, BoolToJS))

void WrapPlayerTextDraw(IPlayerTextDraw *playerTextDraw, v8::Local<v8::Context> context) {
    auto textDrawHandle = CREATE_INSTANCE(IPlayerTextDraw, playerTextDraw, context);

    playerTextDraw->addExtension(new IHandleStorage(context->GetIsolate(), textDrawHandle), true);
}
