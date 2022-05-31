#include "../../logger.hpp"
#include "textdraw_pool_wrapper.hpp"
#include "textdraw_wrapper.hpp"
#include "textdraw_event_dispatcher_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/entity.hpp"
#include "../entry_handler.hpp"
#include "../pool/read_only_pool_wrapper.hpp"
#include "../pool/pool_wrapper.hpp"

WRAP_BASIC(ITextDrawsComponent)

WRAP_BASIC_CALL_RETURN_OVERLOAD(ITextDrawsComponent,
                                create,
                                (create, info[0]->IsNumber(), (ITextDraw
                                    * , EntityToJS<ITextDraw>), (Vector2, JSToVector<Vector2>, position), (int, JSToInt<
                                    int>, model)),
                                (create, true, (ITextDraw
                                    * , EntityToJS<ITextDraw>), (Vector2, JSToVector<Vector2>, position), (Impl::String, JSToString, text)))

WRAP_LOCAL_EXT_HANDLE_STORAGE_GET(ITextDrawsComponent, getEventDispatcher, EventDispatcherHandleStorage)

WRAP_READ_ONLY_POOL_METHODS(ITextDrawsComponent, ITextDraw, EntityToJS<ITextDraw>)
WRAP_POOL_METHODS(ITextDrawsComponent, ITextDraw)

NodeJSEntryHandler<ITextDraw> *handler;

void WrapTextDrawPool(ITextDrawsComponent *textDrawPool, v8::Local<v8::Context> context) {
    handler = new NodeJSEntryHandler<ITextDraw>(context, WrapTextDraw);
    textDrawPool->getPoolEventDispatcher().addEventHandler(handler);
    textDrawPool->addExtension(handler, true);

    auto textDrawPoolHandle = InterfaceToObject(textDrawPool, context, WRAPPED_METHODS(ITextDrawsComponent));
    textDrawPool->addExtension(new IHandleStorage(context->GetIsolate(), textDrawPoolHandle), true);

    auto eventDispatcherHandleStorage = WrapTextDrawEventDispatcher(&textDrawPool->getEventDispatcher(), context);
    textDrawPool->addExtension(eventDispatcherHandleStorage, true);

    auto poolEventDispatcherHandleStorage =
        WRAPPED_POOL_EVENT_DISPATCHER(ITextDraw)(&textDrawPool->getPoolEventDispatcher(), context);
    textDrawPool->addExtension(poolEventDispatcherHandleStorage, true);
}