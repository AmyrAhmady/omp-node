#include "player.hpp"
#include "primitive.hpp"
#include "types.hpp"
#include "actor.hpp"
#include "../wrapper/utils.hpp"

OBJECT_CONVERTER_DEFINE_TO_JS(ActorSpawnData,
                              (Vector3, position, VectorToJS<Vector3>, JSToVector<Vector3>),
                              (float, facingAngle, FloatToJS, JSToFloat),
                              (int, skin, IntToJS, JSToInt))
