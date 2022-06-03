#include "entity_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"

#include "Server/Components/Vehicles/vehicles.hpp"
#include "Server/Components/Actors/actors.hpp"
#include "Server/Components/Objects/objects.hpp"
#include "Server/Components/Pickups/pickups.hpp"
#include "Server/Components/TextLabels/textlabels.hpp"
#include "../../converter/entity.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR_INHERIT(IEntity, IIDProvider)

WRAP_POLYMORPHIC_BASIC_CODE(IEntity, getPosition, {
    POLYMORPHIC_BASIC_CALL_RETURN(IActor, getPosition, (Vector3, VectorToJS<Vector3>))
    POLYMORPHIC_BASIC_CALL_RETURN(IObject, getPosition, (Vector3, VectorToJS<Vector3>))
    POLYMORPHIC_BASIC_CALL_RETURN(IPlayerObject, getPosition, (Vector3, VectorToJS<Vector3>))
    POLYMORPHIC_BASIC_CALL_RETURN(IPickup, getPosition, (Vector3, VectorToJS<Vector3>))

    POLYMORPHIC_BASIC_CALL_RETURN(ITextLabel, getPosition, (Vector3, VectorToJS<Vector3>))
    POLYMORPHIC_BASIC_CALL_RETURN(IPlayerTextLabel, getPosition, (Vector3, VectorToJS<Vector3>))

    POLYMORPHIC_BASIC_CALL_RETURN(IVehicle, getPosition, (Vector3, VectorToJS<Vector3>))
    POLYMORPHIC_BASIC_CALL_RETURN(IPlayer, getPosition, (Vector3, VectorToJS<Vector3>))
})
WRAP_POLYMORPHIC_BASIC_CODE(IEntity, setPosition, {
    POLYMORPHIC_BASIC_CALL(IActor, setPosition, (Vector3, JSToVector<Vector3>, position))
    POLYMORPHIC_BASIC_CALL(IObject, setPosition, (Vector3, JSToVector<Vector3>, position))
    POLYMORPHIC_BASIC_CALL(IPlayerObject, setPosition, (Vector3, JSToVector<Vector3>, position))
    POLYMORPHIC_BASIC_CALL(IPickup, setPosition, (Vector3, JSToVector<Vector3>, position))

    POLYMORPHIC_BASIC_CALL(ITextLabel, setPosition, (Vector3, JSToVector<Vector3>, position))
    POLYMORPHIC_BASIC_CALL(IPlayerTextLabel, setPosition, (Vector3, JSToVector<Vector3>, position))

    POLYMORPHIC_BASIC_CALL(IVehicle, setPosition, (Vector3, JSToVector<Vector3>, position))
    POLYMORPHIC_BASIC_CALL(IPlayer, setPosition, (Vector3, JSToVector<Vector3>, position))
})
WRAP_POLYMORPHIC_BASIC_CODE(IEntity, getRotation, {
    POLYMORPHIC_BASIC_CALL_RETURN(IActor, getRotation, (GTAQuat, GTAQuatToJS))
    POLYMORPHIC_BASIC_CALL_RETURN(IObject, getRotation, (GTAQuat, GTAQuatToJS))
    POLYMORPHIC_BASIC_CALL_RETURN(IPlayerObject, getRotation, (GTAQuat, GTAQuatToJS))
    POLYMORPHIC_BASIC_CALL_RETURN(IPickup, getRotation, (GTAQuat, GTAQuatToJS))

    POLYMORPHIC_BASIC_CALL_RETURN(ITextLabel, getRotation, (GTAQuat, GTAQuatToJS))
    POLYMORPHIC_BASIC_CALL_RETURN(IPlayerTextLabel, getRotation, (GTAQuat, GTAQuatToJS))

    POLYMORPHIC_BASIC_CALL_RETURN(IVehicle, getRotation, (GTAQuat, GTAQuatToJS))
    POLYMORPHIC_BASIC_CALL_RETURN(IPlayer, getRotation, (GTAQuat, GTAQuatToJS))
})
WRAP_POLYMORPHIC_BASIC_CODE(IEntity, setRotation, {
    POLYMORPHIC_BASIC_CALL(IActor, setRotation, (GTAQuat, JSToGTAQuat, rotation))
    POLYMORPHIC_BASIC_CALL(IObject, setRotation, (GTAQuat, JSToGTAQuat, rotation))
    POLYMORPHIC_BASIC_CALL(IPlayerObject, setRotation, (GTAQuat, JSToGTAQuat, rotation))
    POLYMORPHIC_BASIC_CALL(IPickup, setRotation, (GTAQuat, JSToGTAQuat, rotation))

    POLYMORPHIC_BASIC_CALL(ITextLabel, setRotation, (GTAQuat, JSToGTAQuat, rotation))
    POLYMORPHIC_BASIC_CALL(IPlayerTextLabel, setRotation, (GTAQuat, JSToGTAQuat, rotation))

    POLYMORPHIC_BASIC_CALL(IVehicle, setRotation, (GTAQuat, JSToGTAQuat, rotation))
    POLYMORPHIC_BASIC_CALL(IPlayer, setRotation, (GTAQuat, JSToGTAQuat, rotation))
})
WRAP_POLYMORPHIC_BASIC_CODE(IEntity, getVirtualWorld, {
    POLYMORPHIC_BASIC_CALL_RETURN(IActor, getVirtualWorld, (int, IntToJS))
    POLYMORPHIC_BASIC_CALL_RETURN(IObject, getVirtualWorld, (int, IntToJS))
    POLYMORPHIC_BASIC_CALL_RETURN(IPlayerObject, getVirtualWorld, (int, IntToJS))
    POLYMORPHIC_BASIC_CALL_RETURN(IPickup, getVirtualWorld, (int, IntToJS))

    POLYMORPHIC_BASIC_CALL_RETURN(ITextLabel, getVirtualWorld, (int, IntToJS))
    POLYMORPHIC_BASIC_CALL_RETURN(IPlayerTextLabel, getVirtualWorld, (int, IntToJS))

    POLYMORPHIC_BASIC_CALL_RETURN(IVehicle, getVirtualWorld, (int, IntToJS))
    POLYMORPHIC_BASIC_CALL_RETURN(IPlayer, getVirtualWorld, (int, IntToJS))
})
WRAP_POLYMORPHIC_BASIC_CODE(IEntity, setVirtualWorld, {
    POLYMORPHIC_BASIC_CALL(IActor, setVirtualWorld, (int, JSToInt, vw))
    POLYMORPHIC_BASIC_CALL(IObject, setVirtualWorld, (int, JSToInt, vw))
    POLYMORPHIC_BASIC_CALL(IPlayerObject, setVirtualWorld, (int, JSToInt, vw))
    POLYMORPHIC_BASIC_CALL(IPickup, setVirtualWorld, (int, JSToInt, vw))

    POLYMORPHIC_BASIC_CALL(ITextLabel, setVirtualWorld, (int, JSToInt, vw))
    POLYMORPHIC_BASIC_CALL(IPlayerTextLabel, setVirtualWorld, (int, JSToInt, vw))

    POLYMORPHIC_BASIC_CALL(IVehicle, setVirtualWorld, (int, JSToInt, vw))
    POLYMORPHIC_BASIC_CALL(IPlayer, setVirtualWorld, (int, JSToInt, vw))
})

