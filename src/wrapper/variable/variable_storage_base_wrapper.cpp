#include "../../logger.hpp"
#include "variable_storage_base_wrapper.hpp"
#include "../../converter/types.hpp"
#include "../../converter/entity.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR(IVariableStorageBase)

#define ALL_TYPES_IVariableStorageBase IVariablesComponent, IPlayerVariableData

WRAP_POLYMORPHIC_BASIC_CALL(IVariableStorageBase, (ALL_TYPES_IVariableStorageBase), setString, (Impl::String, JSToString, key), (Impl::String, JSToString, value))
WRAP_POLYMORPHIC_BASIC_CALL_RETURN(IVariableStorageBase, (ALL_TYPES_IVariableStorageBase),
                       getString,
                       (const StringView, TO_JS_FN(StringView)),
                       (Impl::String, JSToString, key))
WRAP_POLYMORPHIC_BASIC_CALL(IVariableStorageBase, (ALL_TYPES_IVariableStorageBase), setInt, (Impl::String, JSToString, key), (int, JSToInt<int>, value))
WRAP_POLYMORPHIC_BASIC_CALL_RETURN(IVariableStorageBase, (ALL_TYPES_IVariableStorageBase), getInt, (int, IntToJS<int>), (Impl::String, JSToString, key))
WRAP_POLYMORPHIC_BASIC_CALL(IVariableStorageBase, (ALL_TYPES_IVariableStorageBase), setFloat, (Impl::String, JSToString, key), (float, JSToFloat, value))
WRAP_POLYMORPHIC_BASIC_CALL_RETURN(IVariableStorageBase, (ALL_TYPES_IVariableStorageBase), getFloat, (float, FloatToJS), (Impl::String, JSToString, key))
WRAP_POLYMORPHIC_BASIC_CALL_RETURN(IVariableStorageBase, (ALL_TYPES_IVariableStorageBase),
                       getType,
                       (VariableType, EnumToJS<VariableType>),
                       (Impl::String, JSToString, key))
WRAP_POLYMORPHIC_BASIC_CALL_RETURN(IVariableStorageBase, (ALL_TYPES_IVariableStorageBase), erase, (bool, BoolToJS), (Impl::String, JSToString, key))
WRAP_POLYMORPHIC_BASIC_CODE(IVariableStorageBase, (ALL_TYPES_IVariableStorageBase), getKeyAtIndex, {
    v8::TryCatch tryCatch(isolate);
    int index = JSToInt<int>(info[0], context);
    if (tryCatch.HasCaught()) {
        tryCatch.ReThrow();
        return true;
    }
    StringView key;
    bool value = external->getKeyAtIndex(index, key);
    if (value) {
        info.GetReturnValue().Set(StringViewToJS(key, context));
    } else {
        info.GetReturnValue().Set(v8::Null(isolate));
    }
})
WRAP_POLYMORPHIC_BASIC_CALL_RETURN(IVariableStorageBase, (ALL_TYPES_IVariableStorageBase), size, (int, IntToJS<int>))
