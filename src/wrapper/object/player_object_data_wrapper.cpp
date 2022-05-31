#include "../../logger.hpp"
#include "player_object_data_wrapper.hpp"
#include "player_object_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/entity.hpp"
#include "../../converter/object.hpp"
#include "../entry_handler.hpp"
#include "../pool/read_only_pool_wrapper.hpp"
#include "../pool/pool_wrapper.hpp"

WRAP_BASIC(IPlayerObjectData)

WRAP_BASIC_CALL_RETURN(IPlayerObjectData,
                       create,
                       (IPlayerObject * , EntityToJS<IPlayerObject>),
                       (int, JSToInt, modelID),
                       (Vector3, JSToVector<Vector3>, position),
                       (Vector3, JSToVector<Vector3>, rotation),
                       (float, JSToFloat, drawDist, 0.f))

WRAP_BASIC_CALL(IPlayerObjectData,
                setAttachedObject,
                (int, JSToInt<int>, index),
                (const ObjectAttachmentSlotData&, FROM_JS_FN(ObjectAttachmentSlotData), data))
WRAP_BASIC_CALL(IPlayerObjectData, removeAttachedObject, (int, JSToInt<int>, index))
WRAP_BASIC_CALL_RETURN(IPlayerObjectData, hasAttachedObject, (bool, BoolToJS), (int, JSToInt<int>, index))
WRAP_BASIC_CALL_RETURN(IPlayerObjectData,
                       getAttachedObject,
                       (const ObjectAttachmentSlotData&, TO_JS_FN(ObjectAttachmentSlotData)),
                       (int, JSToInt<int>, index))
WRAP_BASIC_CALL(IPlayerObjectData, beginSelecting)
WRAP_BASIC_CALL_RETURN(IPlayerObjectData, selectingObject, (bool, BoolToJS))
WRAP_BASIC_CALL(IPlayerObjectData, endEditing)
WRAP_BASIC_CALL_OVERLOAD(IPlayerObjectData,
                         beginEditing,
                         (beginEditing, GetValueInterfaceType(info[0], context) == typeid(IObject).name(), (IObject
                             & , JSToEntityRef<IObject>, object)),
                         (beginEditing, GetValueInterfaceType(info[0], context) == typeid(IPlayerObject).name(), (
                             IPlayerObject & , JSToEntityRef<IPlayerObject>, object)))
WRAP_BASIC_CALL_RETURN(IPlayerObjectData, editingObject, (bool, BoolToJS))
WRAP_BASIC_CALL(IPlayerObjectData, editAttachedObject, (int, JSToInt<int>, index));

WRAP_READ_ONLY_POOL_METHODS(IPlayerObjectData, IPlayerObject, EntityToJS<IPlayerObject>)

/** Pool methods */
WRAP_BASIC_CALL(IPlayerObjectData, release, (int, JSToInt<int>, index))
WRAP_BASIC_CALL(IPlayerObjectData, lock, (int, JSToInt<int>, index))
WRAP_BASIC_CALL(IPlayerObjectData, unlock, (int, JSToInt<int>, index))
WRAP_BASIC_CALL_RETURN(IPlayerObjectData, count, (size_t, IntToJS<size_t>))
WRAP_POOL_EVENT_DISPATCHER_CUSTOM_STORAGE(IPlayerObjectData,
                                          IPlayerObject,
                                          PlayerObjectPoolEventDispatcherHandleStorage)
WRAP_BASIC_CODE(IPlayerObjectData, getPoolEventDispatcher, {
    ENTER_FUNCTION_CALLBACK(info)
    auto extensible = GetClosestExtensiblePointer<IPlayer>(info);
    if (extensible == nullptr) {
        return;
    }
    auto storageExtension = queryExtension<PlayerObjectPoolEventDispatcherHandleStorage>(extensible);
    auto handle = storageExtension->get();
    info.GetReturnValue().Set(handle);
})

NodeJSEntryHandler<IPlayerObject> *handler;

std::vector<IExtension *> WrapPlayerObjectData(IPlayer *player,
                                                   IPlayerObjectData *objectPool,
                                                   v8::Local<v8::Context> context) {
    std::vector<IExtension *> handleStorages;

    handler = new NodeJSEntryHandler<IPlayerObject>(context, WrapPlayerObject);
    objectPool->getPoolEventDispatcher().addEventHandler(handler);
    handleStorages.push_back(handler);

    auto objectPoolHandle = InterfaceToObject(objectPool, context, WRAPPED_METHODS(IPlayerObjectData), player);
    handleStorages.push_back(new PlayerObjectPoolHandleStorage(context->GetIsolate(), objectPoolHandle));

    auto poolEventDispatcherHandleStorage =
        WRAPPED_POOL_EVENT_DISPATCHER(IPlayerObject)(&objectPool->getPoolEventDispatcher(), context);
    handleStorages.push_back(poolEventDispatcherHandleStorage);

    return handleStorages;
}