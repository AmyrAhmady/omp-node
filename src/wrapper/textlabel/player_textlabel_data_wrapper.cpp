#include "../../logger.hpp"
#include "player_textlabel_data_wrapper.hpp"
#include "player_textlabel_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/entity.hpp"
#include "../entry_handler.hpp"
#include "Server/Components/Vehicles/vehicles.hpp"
#include "../pool/read_only_pool_wrapper.hpp"
#include "../pool/pool_wrapper.hpp"

WRAP_BASIC(IPlayerTextLabelData)

WRAP_BASIC_CALL_RETURN_OVERLOAD(IPlayerTextLabelData,
                                create,
                                (create, info[6]->IsUndefined(), (IPlayerTextLabel
                                    * , EntityToJS<IPlayerTextLabel>), (Impl::String, JSToString, text), (Colour, JSToColour, colour), (Vector3, JSToVector<
                                    Vector3>, pos), (float, JSToFloat, drawDist), (bool, JSToBool, los)),
                                (create, GetValueInterfaceType(info[6], context) == typeid(IPlayer).name(), (
                                    IPlayerTextLabel
                                        * , EntityToJS<IPlayerTextLabel>), (Impl::String, JSToString, text), (Colour, JSToColour, colour), (Vector3, JSToVector<
                                    Vector3>, pos), (float, JSToFloat, drawDist), (bool, JSToBool, los), (IPlayer
                                    & , JSToEntityRef<IPlayer>, attach)),
                                (create, GetValueInterfaceType(info[6], context) == typeid(IVehicle).name(), (
                                    IPlayerTextLabel
                                        * , EntityToJS<IPlayerTextLabel>), (Impl::String, JSToString, text), (Colour, JSToColour, colour), (Vector3, JSToVector<
                                    Vector3>, pos), (float, JSToFloat, drawDist), (bool, JSToBool, los), (IVehicle
                                    & , JSToEntityRef<IVehicle>, attach)))

WRAP_READ_ONLY_POOL_METHODS(IPlayerTextLabelData, IPlayerTextLabel, EntityToJS<IPlayerTextLabel>)

/** Pool methods */
WRAP_POOL_METHODS_WITHOUT_DISPATCHER(IPlayerTextLabelData)

WRAP_POOL_EVENT_DISPATCHER_CUSTOM_STORAGE(IPlayerTextLabelData,
                                          IPlayerTextLabel,
                                          PlayerTextLabelPoolEventDispatcherHandleStorage)
WRAP_BASIC_CODE(IPlayerTextLabelData, getPoolEventDispatcher, {
    auto extensible = GetClosestExtensiblePointer<IPlayer>(info);
    if (extensible == nullptr) {
        return;
    }
    auto storageExtension = queryExtension<PlayerTextLabelPoolEventDispatcherHandleStorage>(extensible);
    auto handle = storageExtension->get();
    info.GetReturnValue().Set(handle);
})

NodeJSEntryHandler<IPlayerTextLabel, 0x04744ea1d0bb6c72> *handler;

std::vector<IExtension *> WrapPlayerTextLabelData(IPlayer *player,
                                                  IPlayerTextLabelData *textLabelPool,
                                                  v8::Local<v8::Context> context) {
    std::vector<IExtension *> handleStorages;

    handler = new NodeJSEntryHandler<IPlayerTextLabel, 0x04744ea1d0bb6c72>(context, WrapPlayerTextLabel);
    textLabelPool->getPoolEventDispatcher().addEventHandler(handler);
    handleStorages.push_back(handler);

    auto textLabelPoolHandle = InterfaceToObject(textLabelPool, context, WRAPPED_METHODS(IPlayerTextLabelData), player);
    handleStorages.push_back(new PlayerTextLabelPoolHandleStorage(context->GetIsolate(), textLabelPoolHandle));

    auto poolEventDispatcherHandleStorage =
        WRAPPED_POOL_EVENT_DISPATCHER(IPlayerTextLabel)(&textLabelPool->getPoolEventDispatcher(), context);
    handleStorages.push_back(poolEventDispatcherHandleStorage);

    return handleStorages;
}