#include "player.hpp"
#include "primitive.hpp"
#include "types.hpp"
#include "class.hpp"
#include "../wrapper/utils.hpp"

OBJECT_CONVERTER_DEFINE_WITH_DEFAULT(PlayerClass,
                                     (PlayerClass{
                                         0,
                                         TEAM_NONE,
                                         {
                                             0,
                                             0,
                                             0
                                         },
                                         0,
                                         {}}),
                                     (int, skin, IntToJS<int>, JSToInt<int>),
                                     (int, team, IntToJS<int>, JSToInt<int>),
                                     (Vector3, spawn, VectorToJS<Vector3>, JSToVector<Vector3>),
                                     (float, angle, FloatToJS, JSToFloat),
                                     (WeaponSlots, weapons, WeaponSlotsToJS, JSToWeaponSlots))
