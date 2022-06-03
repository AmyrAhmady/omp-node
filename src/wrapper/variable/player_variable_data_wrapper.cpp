#include "../../logger.hpp"
#include "player_variable_data_wrapper.hpp"
#include "../../converter/entity.hpp"
#include "variable_storage_base_wrapper.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR_INHERIT(IPlayerVariableData, IVariableStorageBase)

std::vector<IExtension *> WrapPlayerVariableData(IPlayer *player,
                                                 IPlayerVariableData *playerVariableData,
                                                 v8::Local<v8::Context> context) {

    std::vector<IExtension *> handleStorages;

    auto objectPoolHandle = CREATE_INSTANCE_CLOSEST(IPlayerVariableData, playerVariableData, context, player);
    handleStorages.push_back(new PlayerVariableDataHandleStorage(context->GetIsolate(), objectPoolHandle));

    return handleStorages;
}
