#include "../../logger.hpp"
#include "player_variable_data_wrapper.hpp"
#include "../../converter/entity.hpp"
#include "variable_storage_base_wrapper.hpp"

WRAP_BASIC(IPlayerVariableData)

WRAP_VARIABLE_STORAGE_BASE_METHODS(IPlayerVariableData)

std::vector<IHandleStorage *> WrapPlayerVariableData(IPlayer *player,
                                                     IPlayerVariableData *playerVariableData,
                                                     v8::Local<v8::Context> context) {

    std::vector<IHandleStorage *> handleStorages;

    auto
        objectPoolHandle = InterfaceToObject(playerVariableData, context, WRAPPED_METHODS(IPlayerVariableData), player);
    handleStorages.push_back(new PlayerVariableDataHandleStorage(context->GetIsolate(), objectPoolHandle));

    return handleStorages;
}
