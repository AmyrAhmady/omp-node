#include "player.hpp"
#include "primitive.hpp"

//float delta, bool loop, bool lockX, bool lockY, bool freeze, uint32_t time, StringView lib, StringView name

OBJECT_CONVERTER_DEFINE(AnimationData,
                        (float, delta, FloatToJS, JSToFloat),
                        (bool, loop, BoolToJS, JSToBool),
                        (bool, lockX, BoolToJS, JSToBool),
                        (bool, lockY, BoolToJS, JSToBool),
                        (bool, freeze, BoolToJS, JSToBool),
                        (uint32_t, time, UIntToJS, JSToUInt<uint32_t>),
                        (HybridString<16>, lib, StringViewToJS, JSToString),
                        (HybridString<24>, name, StringViewToJS, JSToString))

OBJECT_CONVERTER_DEFINE_TO_JS(PlayerAnimationData,
                              (uint16_t, ID, UIntToJS, JSToUInt<uint16_t>),
                              (uint16_t, flags, UIntToJS, JSToUInt<uint16_t>),
                              (StringView, lib, StringViewToJS, JSToString, data.name().first),
                              (StringView, name, StringViewToJS, JSToString, data.name().second))

OBJECT_CONVERTER_DEFINE(PeerRequestParams)