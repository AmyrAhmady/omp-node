#include "textdraw_wrapper.hpp"
#include "textdraw_base_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/vehicle.hpp"
#include "../../converter/entity.hpp"
#include "../entity/entity_wrapper.hpp"

WRAP_BASIC(IPlayerTextDraw)

WRAP_TEXT_DRAW_BASE_METHODS(IPlayerTextDraw)

WRAP_BASIC_CALL(IPlayerTextDraw, show)
WRAP_BASIC_CALL(IPlayerTextDraw, hide)
WRAP_BASIC_CALL_RETURN(IPlayerTextDraw, isShown, (bool, BoolToJS))

WRAP_IID_PROVIDER_METHODS(IPlayerTextDraw)

void WrapPlayerTextDraw(IPlayerTextDraw *playerTextDraw, v8::Local<v8::Context> context) {
    auto textDrawHandle = InterfaceToObject(playerTextDraw, context, WRAPPED_METHODS(IPlayerTextDraw));

    playerTextDraw->addExtension(new IHandleStorage(context->GetIsolate(), textDrawHandle), true);
}
