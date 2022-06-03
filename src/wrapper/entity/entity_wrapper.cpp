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

#define ALL_TYPE_IEntity IActor, IObject, IPlayerObject, IPickup, IPlayer, ITextLabel, IPlayerTextLabel, IVehicle

WRAP_POLYMORPHIC_BASIC_CALL_RETURN(IEntity, (ALL_TYPE_IEntity), getPosition, (Vector3, VectorToJS<Vector3>))
WRAP_POLYMORPHIC_BASIC_CALL(IEntity, (ALL_TYPE_IEntity), setPosition, (Vector3, JSToVector<Vector3>, position))
WRAP_POLYMORPHIC_BASIC_CALL_RETURN(IEntity, (ALL_TYPE_IEntity), getRotation, (GTAQuat, GTAQuatToJS))
WRAP_POLYMORPHIC_BASIC_CALL(IEntity, (ALL_TYPE_IEntity), setRotation, (GTAQuat, JSToGTAQuat, rotation))
WRAP_POLYMORPHIC_BASIC_CALL_RETURN(IEntity, (ALL_TYPE_IEntity), getVirtualWorld, (int, IntToJS))
WRAP_POLYMORPHIC_BASIC_CALL(IEntity, (ALL_TYPE_IEntity), setVirtualWorld, (int, JSToInt, vw))
