#include "../../logger.hpp"
#include "object_pool_wrapper.hpp"
#include "object_wrapper.hpp"
#include "object_event_dispatcher_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/entity.hpp"
#include "../entry_handler.hpp"
#include "../pool/read_only_pool_wrapper.hpp"
#include "../pool/pool_wrapper.hpp"

WRAP_BASIC(IObjectsComponent)

WRAP_BASIC_CALL_RETURN(IObjectsComponent,
                       create,
                       (IObject * , EntityToJS<IObject>),
                       (int, JSToInt, modelID),
                       (Vector3, JSToVector<Vector3>, position),
                       (Vector3, JSToVector<Vector3>, rotation),
                       (float, JSToFloat, drawDist, 0.f))

WRAP_BASIC_CALL(IObjectsComponent, setDefaultCameraCollision, (bool, JSToBool, collision))
WRAP_BASIC_CALL_RETURN(IObjectsComponent, getDefaultCameraCollision, (bool, BoolToJS))

WRAP_LOCAL_EXT_HANDLE_STORAGE_GET(IObjectsComponent, getEventDispatcher, EventDispatcherHandleStorage)

WRAP_READ_ONLY_POOL_METHODS(IObjectsComponent, IObject, EntityToJS<IObject>)
WRAP_POOL_METHODS(IObjectsComponent, IObject)

NodeJSEntryHandler<IObject> *handler;

void WrapObjectPool(IObjectsComponent *objectPool, v8::Local<v8::Context> context) {
    handler = new NodeJSEntryHandler<IObject>(context, WrapObject);
    objectPool->getPoolEventDispatcher().addEventHandler(handler);
    objectPool->addExtension(handler, true);

    auto objectPoolHandle = InterfaceToObject(objectPool, context, WRAPPED_METHODS(IObjectsComponent));
    objectPool->addExtension(new IHandleStorage(context->GetIsolate(), objectPoolHandle), true);

    auto eventDispatcherHandleStorage = WrapObjectEventDispatcher(&objectPool->getEventDispatcher(), context);
    objectPool->addExtension(eventDispatcherHandleStorage, true);

    auto poolEventDispatcherHandleStorage =
        WRAPPED_POOL_EVENT_DISPATCHER(IObject)(&objectPool->getPoolEventDispatcher(), context);
    objectPool->addExtension(poolEventDispatcherHandleStorage, true);
}