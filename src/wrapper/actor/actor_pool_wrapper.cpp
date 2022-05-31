#include "../../logger.hpp"
#include "actor_pool_wrapper.hpp"
#include "actor_wrapper.hpp"
#include "actor_event_dispatcher_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../entry_handler.hpp"
#include "../pool/read_only_pool_wrapper.hpp"
#include "../pool/pool_wrapper.hpp"
#include "../../converter/entity.hpp"

WRAP_BASIC(IActorsComponent)

WRAP_BASIC_CALL_RETURN(IActorsComponent,
                       create,
                       (IActor * , EntityToJS<IActor>),
                       (int, JSToInt, skin),
                       (Vector3, JSToVector<Vector3>, pos),
                       (float, JSToFloat, angle))

WRAP_LOCAL_EXT_HANDLE_STORAGE_GET(IActorsComponent, getEventDispatcher, EventDispatcherHandleStorage)

WRAP_READ_ONLY_POOL_METHODS(IActorsComponent, IActor, EntityToJS<IActor>)
WRAP_POOL_METHODS(IActorsComponent, IActor)

NodeJSEntryHandler<IActor> *handler;

void WrapActorPool(IActorsComponent *actorPool, v8::Local<v8::Context> context) {
    handler = new NodeJSEntryHandler<IActor>(context, WrapActor);
    actorPool->getPoolEventDispatcher().addEventHandler(handler);
    actorPool->addExtension(handler, true);

    auto actorPoolHandle = InterfaceToObject(actorPool, context, WRAPPED_METHODS(IActorsComponent));
    actorPool->addExtension(new IHandleStorage(context->GetIsolate(), actorPoolHandle), true);

    auto eventDispatcherHandleStorage = WrapActorEventDispatcher(&actorPool->getEventDispatcher(), context);
    actorPool->addExtension(eventDispatcherHandleStorage, true);

    auto poolEventDispatcherHandleStorage =
        WRAPPED_POOL_EVENT_DISPATCHER(IActor)(&actorPool->getPoolEventDispatcher(), context);
    actorPool->addExtension(poolEventDispatcherHandleStorage, true);
}