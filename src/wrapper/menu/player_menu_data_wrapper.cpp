#include "../../logger.hpp"
#include "player_menu_data_wrapper.hpp"
#include "../../converter/entity.hpp"

WRAP_BASIC(IPlayerMenuData)

WRAP_BASIC_CALL_RETURN(IPlayerMenuData, getMenuID, (uint8_t, UIntToJS<uint8_t>))
WRAP_BASIC_CALL(IPlayerMenuData, setMenuID, (uint8_t, JSToUInt<uint8_t>, id))

std::vector<IExtension *> WrapPlayerMenuData(IPlayer *player,
                                                  IPlayerMenuData *playerMenuData,
                                                  v8::Local<v8::Context> context) {

    std::vector<IExtension *> handleStorages;

    auto objectPoolHandle = InterfaceToObject(playerMenuData, context, WRAPPED_METHODS(IPlayerMenuData), player);
    handleStorages.push_back(new PlayerMenuDataHandleStorage(context->GetIsolate(), objectPoolHandle));

    return handleStorages;
}
