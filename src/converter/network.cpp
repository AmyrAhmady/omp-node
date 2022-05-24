#include "network.hpp"
#include "primitive.hpp"
#include "types.hpp"

OBJECT_CONVERTER_DEFINE_WITH_DEFAULT(BanEntry, {""},
                        (PeerAddress::AddressString, address, StringViewToJS, JSToString),
                        (HybridString<MAX_PLAYER_NAME + 1>, name, StringViewToJS, JSToString),
                        (HybridString<32>, reason, StringViewToJS, JSToString),
                        (WorldTimePoint, time, WorldTimePointToJS, JSToWorldTimePoint))
