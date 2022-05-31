#include "../../logger.hpp"
#include "class_pool_wrapper.hpp"
#include "class_wrapper.hpp"
#include "class_event_dispatcher_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"
#include "../../converter/entity.hpp"
#include "../entry_handler.hpp"
#include "../pool/read_only_pool_wrapper.hpp"
#include "../pool/pool_wrapper.hpp"

WRAP_BASIC(IClassesComponent)

WRAP_BASIC_CALL_RETURN(IClassesComponent,
                       create,
                       (IClass * , EntityToJS<IClass>),
                       (int, JSToInt<int>, skin),
                       (int, JSToInt<int>, team),
                       (Vector3, JSToVector<Vector3>, spawn),
                       (float, JSToFloat, angle),
                       (const WeaponSlots&, JSToWeaponSlots, weapons))

WRAP_LOCAL_EXT_HANDLE_STORAGE_GET(IClassesComponent, getEventDispatcher, EventDispatcherHandleStorage)

WRAP_READ_ONLY_POOL_METHODS(IClassesComponent, IClass, EntityToJS<IClass>)
WRAP_POOL_METHODS(IClassesComponent, IClass)

NodeJSEntryHandler<IClass> *handler;

void WrapClassPool(IClassesComponent *classPool, v8::Local<v8::Context> context) {
    handler = new NodeJSEntryHandler<IClass>(context, WrapClass);
    classPool->getPoolEventDispatcher().addEventHandler(handler);
    classPool->addExtension(handler, true);

    auto classPoolHandle = InterfaceToObject(classPool, context, WRAPPED_METHODS(IClassesComponent));
    classPool->addExtension(new IHandleStorage(context->GetIsolate(), classPoolHandle), true);

    auto eventDispatcherHandleStorage = WrapClassEventDispatcher(&classPool->getEventDispatcher(), context);
    classPool->addExtension(eventDispatcherHandleStorage, true);

    auto poolEventDispatcherHandleStorage =
        WRAPPED_POOL_EVENT_DISPATCHER(IClass)(&classPool->getPoolEventDispatcher(), context);
    classPool->addExtension(poolEventDispatcherHandleStorage, true);
}