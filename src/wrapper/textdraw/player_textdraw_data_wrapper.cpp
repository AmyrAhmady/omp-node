#include "../../logger.hpp"
#include "player_textdraw_data_wrapper.hpp"
#include "player_textdraw_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/entity.hpp"
#include "../entry_handler.hpp"
#include "../pool/read_only_pool_wrapper.hpp"
#include "../pool/pool_wrapper.hpp"

WRAP_BASIC(IPlayerTextDrawData)

WRAP_BASIC_CALL_RETURN_OVERLOAD(IPlayerTextDrawData,
                                create,
                                (create, info[0]->IsNumber(), (IPlayerTextDraw
                                    * , EntityToJS<IPlayerTextDraw>), (Vector2, JSToVector<Vector2>, position), (int, JSToInt<
                                    int>, model)),
                                (create, true, (IPlayerTextDraw * , EntityToJS<IPlayerTextDraw>), (Vector2, JSToVector<
                                    Vector2>, position), (Impl::String, JSToString, text)))

WRAP_BASIC_CALL(IPlayerTextDrawData, beginSelection, (Colour, JSToColour, highlight))
WRAP_BASIC_CALL_RETURN(IPlayerTextDrawData, isSelecting, (bool, BoolToJS))
WRAP_BASIC_CALL(IPlayerTextDrawData, endSelection)

WRAP_READ_ONLY_POOL_METHODS(IPlayerTextDrawData, IPlayerTextDraw, EntityToJS<IPlayerTextDraw>)

/** Pool methods */
WRAP_BASIC_CALL(IPlayerTextDrawData, release, (int, JSToInt<int>, index))
WRAP_BASIC_CALL(IPlayerTextDrawData, lock, (int, JSToInt<int>, index))
WRAP_BASIC_CALL(IPlayerTextDrawData, unlock, (int, JSToInt<int>, index))
WRAP_BASIC_CALL_RETURN(IPlayerTextDrawData, count, (size_t, IntToJS<size_t>))
WRAP_POOL_EVENT_DISPATCHER_CUSTOM_STORAGE(IPlayerTextDrawData,
                                          IPlayerTextDraw,
                                          PlayerTextDrawPoolEventDispatcherHandleStorage)
WRAP_BASIC_CODE(IPlayerTextDrawData, getPoolEventDispatcher, {
    ENTER_FUNCTION_CALLBACK(info)
    auto extensible = GetClosestExtensiblePointer<IPlayer>(info);
    if (extensible == nullptr) {
        return;
    }
    auto storageExtension = queryExtension<PlayerTextDrawPoolEventDispatcherHandleStorage>(extensible);
    auto handle = storageExtension->get();
    info.GetReturnValue().Set(handle);
})

NodeJSEntryHandler<IPlayerTextDraw, 0xee34d201850083ca> *handler;

std::vector<IExtension *> WrapPlayerTextDrawData(IPlayer *player,
                                                 IPlayerTextDrawData *textDrawPool,
                                                 v8::Local<v8::Context> context) {
    std::vector<IExtension *> handleStorages;

    handler = new NodeJSEntryHandler<IPlayerTextDraw, 0xee34d201850083ca>(context, WrapPlayerTextDraw);
    textDrawPool->getPoolEventDispatcher().addEventHandler(handler);
    handleStorages.push_back(handler);

    auto textDrawPoolHandle = InterfaceToObject(textDrawPool, context, WRAPPED_METHODS(IPlayerTextDrawData), player);
    handleStorages.push_back(new PlayerTextDrawPoolHandleStorage(context->GetIsolate(), textDrawPoolHandle));

    auto poolEventDispatcherHandleStorage =
        WRAPPED_POOL_EVENT_DISPATCHER(IPlayerTextDraw)(&textDrawPool->getPoolEventDispatcher(), context);
    handleStorages.push_back(poolEventDispatcherHandleStorage);

    return handleStorages;
}