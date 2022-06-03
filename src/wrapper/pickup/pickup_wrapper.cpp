#include "pickup_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/vehicle.hpp"
#include "../../converter/entity.hpp"
#include "../entity/entity_wrapper.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR_INHERIT(IPickup, IEntity)

WRAP_BASIC_CALL(IPickup, setType, (PickupType, JSToUInt<PickupType>, type), (bool, JSToBool, update, true))

WRAP_BASIC_CALL_RETURN(IPickup, getType, (PickupType, UIntToJS<PickupType>))

WRAP_BASIC_CALL(IPickup, setPositionNoUpdate, (Vector3, JSToVector<Vector3>, position))

WRAP_BASIC_CALL(IPickup, setModel, (int, JSToInt, id), (bool, JSToBool, update, true))

WRAP_BASIC_CALL_RETURN(IPickup, getModel, (int, IntToJS))

WRAP_BASIC_CALL_RETURN(IPickup,
                       isStreamedInForPlayer,
                       (bool, BoolToJS),
                       (const IPlayer&, JSToEntityRef<IPlayer>, player))

WRAP_BASIC_CALL(IPickup, streamInForPlayer, (IPlayer & , JSToEntityRef<IPlayer>, player))

WRAP_BASIC_CALL(IPickup, streamOutForPlayer, (IPlayer & , JSToEntityRef<IPlayer>, player))

WRAP_BASIC_CALL(IPickup,
                setPickupHiddenForPlayer,
                (IPlayer & , JSToEntityRef<IPlayer>, player),
                (bool, JSToBool, hidden))

WRAP_BASIC_CALL_RETURN(IPickup, isPickupHiddenForPlayer, (bool, BoolToJS), (IPlayer & , JSToEntityRef<IPlayer>, player))

void WrapPickup(IPickup *pickup, v8::Local<v8::Context> context) {
    auto pickupHandle = CREATE_INSTANCE(IPickup, pickup, context);

    pickup->addExtension(new IHandleStorage(context->GetIsolate(), pickupHandle), true);
}