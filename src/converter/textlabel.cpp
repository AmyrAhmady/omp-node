#include "player.hpp"
#include "primitive.hpp"
#include "types.hpp"
#include "textlabel.hpp"
#include "../wrapper/utils.hpp"

OBJECT_CONVERTER_DEFINE_TO_JS(TextLabelAttachmentData,
                              (int, playerID, IntToJS, JSToInt),
                              (int, vehicleID, IntToJS, JSToInt))
