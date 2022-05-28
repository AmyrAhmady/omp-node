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

WRAP_BASIC_CODE(IActorsComponent, getEventDispatcher, {
    ENTER_FUNCTION_CALLBACK(info)
    auto pool = GetContextExternalPointer<IActorsComponent>(info);
    auto dispatcher = &pool->getEventDispatcher();
    auto dispatcherHandle = WrapActorEventDispatcher(dispatcher, context);
    info.GetReturnValue().Set(dispatcherHandle);
})

WRAP_READ_ONLY_POOL_METHODS(IActorsComponent, IActor, EntityToJS<IActor>)
WRAP_POOL_METHODS(IActorsComponent, IActor)

NodeJSEntryHandler<IActor> *handler;

void WrapActorPool(IActorsComponent *actorPool, v8::Local<v8::Context> context) {
    handler = new NodeJSEntryHandler<IActor>(context, WrapActor); // todo: store somewhere to delete later

    actorPool->getPoolEventDispatcher().addEventHandler(handler);

    auto actorPoolHandle = InterfaceToObject(actorPool, context, WRAPPED_METHODS(IActorsComponent));

    actorPool->addExtension(new IHandleStorage(context->GetIsolate(), actorPoolHandle), true);
}