#include "textdraw_wrapper.hpp"
#include "textdraw_base_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/vehicle.hpp"
#include "../../converter/entity.hpp"
#include "../entity/entity_wrapper.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR_INHERIT(ITextDraw, ITextDrawBase)

WRAP_BASIC_CALL(ITextDraw, showForPlayer, (IPlayer & , JSToEntityRef<IPlayer>, player))
WRAP_BASIC_CALL(ITextDraw, hideForPlayer, (IPlayer & , JSToEntityRef<IPlayer>, player))
WRAP_BASIC_CALL_RETURN(ITextDraw, isShownForPlayer, (bool, BoolToJS), (IPlayer & , JSToEntityRef<IPlayer>, player))
WRAP_BASIC_CALL(ITextDraw,
                setTextForPlayer,
                (IPlayer & , JSToEntityRef<IPlayer>, player),
                (Impl::String, JSToString, text))

void WrapTextDraw(ITextDraw *textDraw, v8::Local<v8::Context> context) {
    auto textDrawHandle = CREATE_INSTANCE(ITextDraw, textDraw, context);

    textDraw->addExtension(new IHandleStorage(context->GetIsolate(), textDrawHandle), true);
}
