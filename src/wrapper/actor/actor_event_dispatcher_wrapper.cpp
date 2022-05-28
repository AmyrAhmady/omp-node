#include <utility>

#include "actor_wrapper.hpp"
#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"
#include "../../converter/actor.hpp"
#include "actor_event_dispatcher_wrapper.hpp"

WRAP_BASIC(IActorEventDispatcher)
WRAP_HANDLER_BASIC(ActorEventHandler, NodeJSActorEventHandler)

WRAP_HANDLER(NodeJSActorEventHandler, void, onPlayerGiveDamageActor, 5, {
    args[0] = IPlayerToJS(player, context);
    args[1] = IActorToJS(actor, context);
    args[2] = FloatToJS(amount, context);
    args[3] = UIntToJS<unsigned>(weapon, context);
    args[4] = EnumToJS(part, context);
}, return, return, IPlayer& player, IActor& actor, float amount, unsigned weapon, BodyPart part)

WRAP_HANDLER(NodeJSActorEventHandler, void, onActorStreamOut, 2, {
    args[0] = IActorToJS(actor, context);
    args[1] = IPlayerToJS(forPlayer, context);
}, return, return, IActor& actor, IPlayer& forPlayer)

WRAP_HANDLER(NodeJSActorEventHandler, void, onActorStreamIn, 2, {
    args[0] = IActorToJS(actor, context);
    args[1] = IPlayerToJS(forPlayer, context);
}, return, return, IActor& actor, IPlayer& forPlayer)

WRAP_BASIC_CODE(IActorEventDispatcher, addEventHandler, WRAP_ADD_EVENT_HANDLER(NodeJSActorEventHandler))
WRAP_BASIC_CODE(IActorEventDispatcher, hasEventHandler, WRAP_HAS_EVENT_HANDLER(NodeJSActorEventHandler))
WRAP_BASIC_CODE(IActorEventDispatcher, removeEventHandler, WRAP_REMOVE_EVENT_HANDLER(NodeJSActorEventHandler))

WRAP_BASIC_CALL_RETURN(IActorEventDispatcher, count, (size_t, UIntToJS))

v8::Local<v8::Value> WrapActorEventDispatcher(IEventDispatcher<ActorEventHandler> *dispatcher,
                                               v8::Local<v8::Context> context) {

    v8::EscapableHandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(dispatcher, context, WRAPPED_METHODS(IActorEventDispatcher));

    return hs.Escape(dispatcherHandle);
}