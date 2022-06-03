#include "id_provider_wrapper.hpp"
#include "Server/Components/Vehicles/vehicles.hpp"
#include "Server/Components/Actors/actors.hpp"
#include "Server/Components/Classes/classes.hpp"
#include "Server/Components/GangZones/gangzones.hpp"
#include "Server/Components/Menus/menus.hpp"
#include "Server/Components/Objects/objects.hpp"
#include "Server/Components/Pickups/pickups.hpp"
#include "Server/Components/TextDraws/textdraws.hpp"
#include "Server/Components/TextLabels/textlabels.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR(IIDProvider)

WRAP_POLYMORPHIC_BASIC_CODE(IIDProvider, getID, {
    POLYMORPHIC_BASIC_CALL_RETURN(IActor, getID, (int, IntToJS))
    POLYMORPHIC_BASIC_CALL_RETURN(IClass, getID, (int, IntToJS))
    POLYMORPHIC_BASIC_CALL_RETURN(IGangZone, getID, (int, IntToJS))
    POLYMORPHIC_BASIC_CALL_RETURN(IMenu, getID, (int, IntToJS))

    POLYMORPHIC_BASIC_CALL_RETURN(IObject, getID, (int, IntToJS))
    POLYMORPHIC_BASIC_CALL_RETURN(IPlayerObject, getID, (int, IntToJS))

    POLYMORPHIC_BASIC_CALL_RETURN(IPickup, getID, (int, IntToJS))

    POLYMORPHIC_BASIC_CALL_RETURN(IPlayer, getID, (int, IntToJS))

    POLYMORPHIC_BASIC_CALL_RETURN(ITextDraw, getID, (int, IntToJS))
    POLYMORPHIC_BASIC_CALL_RETURN(IPlayerTextDraw, getID, (int, IntToJS))

    POLYMORPHIC_BASIC_CALL_RETURN(ITextLabel, getID, (int, IntToJS))
    POLYMORPHIC_BASIC_CALL_RETURN(IPlayerTextLabel, getID, (int, IntToJS))

    POLYMORPHIC_BASIC_CALL_RETURN(IVehicle, getID, (int, IntToJS))
})
