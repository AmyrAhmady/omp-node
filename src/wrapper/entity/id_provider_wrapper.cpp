#include "id_provider_wrapper.hpp"
#include "../../converter/primitive.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR(IIDProvider)

WRAP_BASIC_CALL_RETURN(IIDProvider, getID, (int, IntToJS))

