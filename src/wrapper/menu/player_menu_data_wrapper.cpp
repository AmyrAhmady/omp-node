#include "../../logger.hpp"
#include "player_menu_data_wrapper.hpp"
#include "../../converter/entity.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR(IPlayerMenuData)

WRAP_BASIC_CALL_RETURN(IPlayerMenuData, getMenuID, (uint8_t, UIntToJS<uint8_t>))
WRAP_BASIC_CALL(IPlayerMenuData, setMenuID, (uint8_t, JSToUInt<uint8_t>, id))

std::vector<IExtension *> WrapPlayerMenuData(IPlayer *player,
                                             IPlayerMenuData *playerMenuData,
                                             v8::Local<v8::Context> context) {

    std::vector<IExtension *> handleStorages;

    auto objectPoolHandle = CREATE_INSTANCE_CLOSEST(IPlayerMenuData, playerMenuData, context, player);
    handleStorages.push_back(new PlayerMenuDataHandleStorage(context->GetIsolate(), objectPoolHandle));

    return handleStorages;
}
