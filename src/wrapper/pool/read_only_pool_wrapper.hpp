#pragma once

typedef Pair<int, int> PairInt;

#define WRAP_READ_ONLY_POOL_METHODS(Type, EntityType, ConvertEntityToJSFn) \
    WRAP_BASIC_CALL_RETURN(Type, get, (EntityType *, ConvertEntityToJSFn), (int, JSToInt<int>, index)) \
    WRAP_BASIC_CALL_RETURN(Type, bounds, (PairInt, PairIntToJS))
