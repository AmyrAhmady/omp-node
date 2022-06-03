#include "../../logger.hpp"
#include "player_class_data_wrapper.hpp"
#include "../../converter/entity.hpp"
#include "../../converter/class.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR(IPlayerClassData)

WRAP_BASIC_CALL_RETURN(IPlayerClassData, getClass, (const PlayerClass&, PlayerClassToJS))
WRAP_BASIC_CALL(IPlayerClassData, setSpawnInfo, (const PlayerClass &, JSToPlayerClass, classInfo))

std::vector<IExtension *> WrapPlayerClassData(IPlayer *player,
                                              IPlayerClassData *playerClassData,
                                              v8::Local<v8::Context> context) {

    std::vector<IExtension *> handleStorages;

    auto objectPoolHandle = CREATE_INSTANCE_CLOSEST(IPlayerClassData, playerClassData, context, player);
    handleStorages.push_back(new PlayerClassDataHandleStorage(context->GetIsolate(), objectPoolHandle));

    return handleStorages;
}
