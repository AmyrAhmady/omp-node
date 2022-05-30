#include "player.hpp"
#include "primitive.hpp"
#include "types.hpp"
#include "object.hpp"
#include "../wrapper/utils.hpp"

OBJECT_CONVERTER_DEFINE(ObjectAttachmentSlotData,
                        (int, model, IntToJS, JSToInt),
                        (int, bone, IntToJS, JSToInt),
                        (Vector3, offset, VectorToJS<Vector3>, JSToVector<Vector3>),
                        (Vector3, rotation, VectorToJS<Vector3>, JSToVector<Vector3>),
                        (Vector3, scale, VectorToJS<Vector3>, JSToVector<Vector3>),
                        (Colour, colour1, ColourToJS, JSToColour),
                        (Colour, colour2, ColourToJS, JSToColour))

OBJECT_CONVERTER_DEFINE(ObjectMoveData,
                        (Vector3, targetPos, VectorToJS<Vector3>, JSToVector<Vector3>),
                        (Vector3, targetRot, VectorToJS<Vector3>, JSToVector<Vector3>),
                        (float, speed, FloatToJS, JSToFloat))

OBJECT_CONVERTER_DEFINE(ObjectAttachmentData,
                        (ObjectAttachmentData::Type, type, EnumToJS<ObjectAttachmentData::Type>, JSToEnum<
                            ObjectAttachmentData::Type>),
                        (bool, syncRotation, BoolToJS, JSToBool),
                        (int, ID, IntToJS<int>, JSToInt<int>),
                        (Vector3, offset, VectorToJS<Vector3>, JSToVector<Vector3>),
                        (Vector3, rotation, VectorToJS<Vector3>, JSToVector<Vector3>))

OBJECT_CONVERTER_DEFINE_TO_JS(ObjectMaterialData,
                              (int, model, IntToJS<int>, JSToInt<int>),
                              (uint8_t, materialSize, UIntToJS<uint8_t>, JSToUInt<uint8_t>),
                              (uint8_t, fontSize, UIntToJS<uint8_t>, JSToUInt<uint8_t>),
                              (uint8_t, alignment, UIntToJS<uint8_t>, JSToUInt<uint8_t>),
                              (bool, bold, BoolToJS, JSToBool),
                              (Colour, materialColour, ColourToJS, JSToColour),
                              (Colour, fontColour, ColourToJS, JSToColour),
                              (Colour, backgroundColour, ColourToJS, JSToColour),
                              (HybridString<32>, textOrTXD, StringViewToJS, JSToString),
                              (HybridString<32>, fontOrTexture, StringViewToJS, JSToString),
                              (ObjectMaterialData::Type, type, EnumToJS<ObjectMaterialData::Type>, JSToEnum<
                                  ObjectMaterialData::Type>),
                              (bool, used, BoolToJS, JSToBool))
