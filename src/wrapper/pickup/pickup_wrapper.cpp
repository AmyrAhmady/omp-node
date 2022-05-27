#include "pickup_wrapper.hpp"
#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"
#include "../../converter/vehicle.hpp"
#include "../entity/entity_wrapper.hpp"

WRAP_BASIC(IPickup)

WRAP_BASIC_CALL(IPickup, setType, (PickupType, JSToUInt<PickupType>, type), (bool, JSToBool, update, true))

WRAP_BASIC_CALL_RETURN(IPickup, getType, (PickupType, UIntToJS<PickupType>))

WRAP_BASIC_CALL(IPickup, setPositionNoUpdate, (Vector3, JSToVector<Vector3>, position))

WRAP_BASIC_CALL(IPickup, setModel, (int, JSToInt, id), (bool, JSToBool, update, true))

WRAP_BASIC_CALL_RETURN(IPickup, getModel, (int, IntToJS))

WRAP_BASIC_CALL_RETURN(IPickup,
                       isStreamedInForPlayer,
                       (bool, BoolToJS),
                       (const IPlayer&, FROM_JS_FN(IPlayerRef), player))

WRAP_BASIC_CALL(IPickup, streamInForPlayer, (IPlayer & , FROM_JS_FN(IPlayerRef), player))

WRAP_BASIC_CALL(IPickup, streamOutForPlayer, (IPlayer & , FROM_JS_FN(IPlayerRef), player))

WRAP_BASIC_CALL(IPickup,
                setPickupHiddenForPlayer,
                (IPlayer & , FROM_JS_FN(IPlayerRef), player),
                (bool, JSToBool, hidden))

WRAP_BASIC_CALL_RETURN(IPickup, isPickupHiddenForPlayer, (bool, BoolToJS), (IPlayer & , FROM_JS_FN(IPlayerRef), player))

WRAP_ENTITY_METHODS(IPickup)

void WrapPickup(IPickup *pickup, v8::Local<v8::Context> context) {
    auto pickupHandle = InterfaceToObject(pickup, context, WRAPPED_METHODS(IPickup));

    pickup->addExtension(new IHandleStorage(context->GetIsolate(), pickupHandle), true);
}