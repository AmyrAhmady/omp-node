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

#define ALL_TYPES_IIDProvider IActor, IClass, IGangZone, IMenu, IObject, IPlayerObject, IPickup, IPlayer, ITextDraw, IPlayerTextDraw, ITextLabel, IPlayerTextLabel, IVehicle

WRAP_POLYMORPHIC_BASIC_CALL_RETURN(IIDProvider, (ALL_TYPES_IIDProvider), getID, (int, IntToJS))
