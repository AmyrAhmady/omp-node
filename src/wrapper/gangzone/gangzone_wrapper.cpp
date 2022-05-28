#include "gangzone_wrapper.hpp"
#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"
#include "../../converter/vehicle.hpp"
#include "../../converter/gangzone.hpp"
#include "../entity/entity_wrapper.hpp"

WRAP_BASIC(IGangZone)

WRAP_BASIC_CALL_RETURN(IGangZone, isShownForPlayer, (bool, BoolToJS), (const IPlayer&, FROM_JS_FN(IPlayerRef), player))
WRAP_BASIC_CALL_RETURN(IGangZone,
                       isFlashingForPlayer,
                       (bool, BoolToJS),
                       (const IPlayer&, FROM_JS_FN(IPlayerRef), player))
WRAP_BASIC_CALL(IGangZone,
                showForPlayer,
                (IPlayer & , FROM_JS_FN(IPlayerRef), player),
                (const Colour&, FROM_JS_FN(Colour), colour))
WRAP_BASIC_CALL(IGangZone, hideForPlayer, (IPlayer & , FROM_JS_FN(IPlayerRef), player))
WRAP_BASIC_CALL(IGangZone,
                flashForPlayer,
                (IPlayer & , FROM_JS_FN(IPlayerRef), player),
                (const Colour&, FROM_JS_FN(Colour), colour))
WRAP_BASIC_CALL(IGangZone, stopFlashForPlayer, (IPlayer & , FROM_JS_FN(IPlayerRef), player))
WRAP_BASIC_CALL_RETURN(IGangZone, getPosition, (GangZonePos, TO_JS_FN(GangZonePos)))
WRAP_BASIC_CALL(IGangZone, setPosition, (const GangZonePos&, FROM_JS_FN(GangZonePos), position))
WRAP_BASIC_CALL_RETURN(IGangZone, isPlayerInside, (bool, BoolToJS), (const IPlayer&, FROM_JS_FN(IPlayerRef), player))
WRAP_BASIC_CALL_RETURN(IGangZone, getShownFor, (const FlatHashSet<IPlayer*>&, TO_JS_FN(FlatPtrHashSetIPlayer)))
WRAP_BASIC_CALL_RETURN(IGangZone,
                       getFlashingColorForPlayer,
                       (const Colour, TO_JS_FN(Colour)),
                       (IPlayer & , FROM_JS_FN(IPlayerRef), player))
WRAP_BASIC_CALL_RETURN(IGangZone,
                       getColorForPlayer,
                       (const Colour, TO_JS_FN(Colour)),
                       (IPlayer & , FROM_JS_FN(IPlayerRef), player))

WRAP_IID_PROVIDER_METHODS(IGangZone)

void WrapGangZone(IGangZone *gangZone, v8::Local<v8::Context> context) {
    auto gangZoneHandle = InterfaceToObject(gangZone, context, WRAPPED_METHODS(IGangZone));

    gangZone->addExtension(new IHandleStorage(context->GetIsolate(), gangZoneHandle), true);
}