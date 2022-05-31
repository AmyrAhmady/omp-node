#include "actor_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/vehicle.hpp"
#include "../../converter/anim.hpp"
#include "../../converter/actor.hpp"
#include "../../converter/entity.hpp"
#include "../entity/entity_wrapper.hpp"

WRAP_BASIC(IActor)

WRAP_BASIC_CALL(IActor, setSkin, (int, JSToInt<int>, id))
WRAP_BASIC_CALL_RETURN(IActor, getSkin, (int, IntToJS<int>))
WRAP_BASIC_CALL(IActor, applyAnimation, (const AnimationData&, FROM_JS_FN(AnimationData), animation))
WRAP_BASIC_CALL_RETURN(IActor, getAnimation, (const AnimationData&, TO_JS_FN(AnimationData)))
WRAP_BASIC_CALL(IActor, clearAnimations)
WRAP_BASIC_CALL(IActor, setHealth, (float, JSToFloat, health))
WRAP_BASIC_CALL_RETURN(IActor, getHealth, (float, FloatToJS))
WRAP_BASIC_CALL(IActor, setInvulnerable, (bool, JSToBool, invuln))
WRAP_BASIC_CALL_RETURN(IActor, isInvulnerable, (bool, BoolToJS))
WRAP_BASIC_CALL_RETURN(IActor,
                       isStreamedInForPlayer,
                       (bool, BoolToJS),
                       (const IPlayer&, JSToEntityRef<IPlayer>, player))
WRAP_BASIC_CALL(IActor, streamInForPlayer, (IPlayer & , JSToEntityRef<IPlayer>, player))
WRAP_BASIC_CALL(IActor, streamOutForPlayer, (IPlayer & , JSToEntityRef<IPlayer>, player))
WRAP_BASIC_CALL_RETURN(IActor, getSpawnData, (const ActorSpawnData&, TO_JS_FN(ActorSpawnData)));

WRAP_ENTITY_METHODS(IActor)

void WrapActor(IActor *actor, v8::Local<v8::Context> context) {
    auto actorHandle = InterfaceToObject(actor, context, WRAPPED_METHODS(IActor));

    actor->addExtension(new IHandleStorage(context->GetIsolate(), actorHandle), true);
}
