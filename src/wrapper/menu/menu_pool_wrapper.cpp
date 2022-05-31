#include "../../logger.hpp"
#include "menu_pool_wrapper.hpp"
#include "menu_wrapper.hpp"
#include "menu_event_dispatcher_wrapper.hpp"
#include "../../converter/types.hpp"
#include "../../converter/entity.hpp"
#include "../entry_handler.hpp"
#include "../pool/read_only_pool_wrapper.hpp"
#include "../pool/pool_wrapper.hpp"

WRAP_BASIC(IMenusComponent)

WRAP_BASIC_CALL_RETURN(IMenusComponent,
                       create,
                       (IMenu * , EntityToJS<IMenu>),
                       (Impl::String, JSToString, title),
                       (Vector2, JSToVector<Vector2>, position),
                       (uint8_t, JSToUInt<uint8_t>, columns),
                       (float, JSToFloat, col1Width),
                       (float, JSToFloat, col2Width))

WRAP_LOCAL_EXT_HANDLE_STORAGE_GET(IMenusComponent, getEventDispatcher, EventDispatcherHandleStorage)

WRAP_READ_ONLY_POOL_METHODS(IMenusComponent, IMenu, EntityToJS<IMenu>)
WRAP_POOL_METHODS(IMenusComponent, IMenu)

NodeJSEntryHandler<IMenu> *handler;

void WrapMenuPool(IMenusComponent *menuPool, v8::Local<v8::Context> context) {
    handler = new NodeJSEntryHandler<IMenu>(context, WrapMenu);
    menuPool->getPoolEventDispatcher().addEventHandler(handler);
    menuPool->addExtension(handler, true);

    auto menuPoolHandle = InterfaceToObject(menuPool, context, WRAPPED_METHODS(IMenusComponent));
    menuPool->addExtension(new IHandleStorage(context->GetIsolate(), menuPoolHandle), true);

    auto eventDispatcherHandleStorage = WrapMenuEventDispatcher(&menuPool->getEventDispatcher(), context);
    menuPool->addExtension(eventDispatcherHandleStorage, true);

    auto poolEventDispatcherHandleStorage =
        WRAPPED_POOL_EVENT_DISPATCHER(IMenu)(&menuPool->getPoolEventDispatcher(), context);
    menuPool->addExtension(poolEventDispatcherHandleStorage, true);
}