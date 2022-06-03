#include "gangzone_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"
#include "../../converter/vehicle.hpp"
#include "../../converter/gangzone.hpp"
#include "../../converter/entity.hpp"
#include "../entity/entity_wrapper.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR_INHERIT(IGangZone, IIDProvider)

WRAP_BASIC_CALL_RETURN(IGangZone, isShownForPlayer, (bool, BoolToJS), (const IPlayer&, JSToEntityRef<IPlayer>, player))
WRAP_BASIC_CALL_RETURN(IGangZone,
                       isFlashingForPlayer,
                       (bool, BoolToJS),
                       (const IPlayer&, JSToEntityRef<IPlayer>, player))
WRAP_BASIC_CALL(IGangZone,
                showForPlayer,
                (IPlayer & , JSToEntityRef<IPlayer>, player),
                (const Colour&, FROM_JS_FN(Colour), colour))
WRAP_BASIC_CALL(IGangZone, hideForPlayer, (IPlayer & , JSToEntityRef<IPlayer>, player))
WRAP_BASIC_CALL(IGangZone,
                flashForPlayer,
                (IPlayer & , JSToEntityRef<IPlayer>, player),
                (const Colour&, FROM_JS_FN(Colour), colour))
WRAP_BASIC_CALL(IGangZone, stopFlashForPlayer, (IPlayer & , JSToEntityRef<IPlayer>, player))
WRAP_BASIC_CALL_RETURN(IGangZone, getPosition, (GangZonePos, TO_JS_FN(GangZonePos)))
WRAP_BASIC_CALL(IGangZone, setPosition, (const GangZonePos&, FROM_JS_FN(GangZonePos), position))
WRAP_BASIC_CALL_RETURN(IGangZone, isPlayerInside, (bool, BoolToJS), (const IPlayer&, JSToEntityRef<IPlayer>, player))
WRAP_BASIC_CALL_RETURN(IGangZone, getShownFor, (const FlatHashSet<IPlayer*>&, TO_JS_FN(FlatPtrHashSetIPlayer)))
WRAP_BASIC_CALL_RETURN(IGangZone,
                       getFlashingColorForPlayer,
                       (const Colour, TO_JS_FN(Colour)),
                       (IPlayer & , JSToEntityRef<IPlayer>, player))
WRAP_BASIC_CALL_RETURN(IGangZone,
                       getColorForPlayer,
                       (const Colour, TO_JS_FN(Colour)),
                       (IPlayer & , JSToEntityRef<IPlayer>, player))

void WrapGangZone(IGangZone *gangZone, v8::Local<v8::Context> context) {
    auto gangZoneHandle = CREATE_INSTANCE(IGangZone, gangZone, context);

    gangZone->addExtension(new IHandleStorage(context->GetIsolate(), gangZoneHandle), true);
}