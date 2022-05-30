#include <utility>

#include "object_wrapper.hpp"
#include "player_object_wrapper.hpp"
#include "../../converter/types.hpp"
#include "../../converter/entity.hpp"
#include "../../converter/object.hpp"
#include "object_event_dispatcher_wrapper.hpp"

WRAP_BASIC(IObjectEventDispatcher)
WRAP_HANDLER_BASIC(ObjectEventHandler, NodeJSObjectEventHandler)

WRAP_HANDLER(NodeJSObjectEventHandler, void, onMoved, 1, {
    args[0] = EntityToJS<IObject>(object, context);
}, return, return, IObject &object)

WRAP_HANDLER(NodeJSObjectEventHandler, void, onPlayerObjectMoved, 2, {
    args[0] = EntityToJS<IPlayer>(player, context);
    args[1] = EntityToJS<IPlayerObject>(object, context);
}, return, return, IPlayer &player, IPlayerObject &object)

WRAP_HANDLER(NodeJSObjectEventHandler, void, onObjectSelected, 4, {
    args[0] = EntityToJS<IPlayer>(player, context);
    args[1] = EntityToJS<IObject>(object, context);
    args[2] = IntToJS<int>(model, context);
    args[3] = VectorToJS<Vector3>(position, context);
}, return, return, IPlayer &player, IObject &object, int model, Vector3 position)

WRAP_HANDLER(NodeJSObjectEventHandler, void, onPlayerObjectSelected, 4, {
    args[0] = EntityToJS<IPlayer>(player, context);
    args[1] = EntityToJS<IPlayerObject>(object, context);
    args[2] = IntToJS<int>(model, context);
    args[3] = VectorToJS<Vector3>(position, context);
}, return, return, IPlayer &player, IPlayerObject &object, int model, Vector3 position)

WRAP_HANDLER(NodeJSObjectEventHandler, void, onObjectEdited, 5, {
    args[0] = EntityToJS<IPlayer>(player, context);
    args[1] = EntityToJS<IObject>(object, context);
    args[2] = EnumToJS<ObjectEditResponse>(response, context);
    args[3] = VectorToJS<Vector3>(offset, context);
    args[4] = VectorToJS<Vector3>(rotation, context);
}, return, return, IPlayer &player, IObject &object, ObjectEditResponse response, Vector3 offset, Vector3 rotation)

WRAP_HANDLER(NodeJSObjectEventHandler,
             void,
             onPlayerObjectEdited,
             5,
             {
                 args[0] = EntityToJS<IPlayer>(player, context);
                 args[1] = EntityToJS<IPlayerObject>(object, context);
                 args[2] = EnumToJS<ObjectEditResponse>(response, context);
                 args[3] = VectorToJS<Vector3>(offset, context);
                 args[4] = VectorToJS<Vector3>(rotation, context);
             },
             return,
             return,
             IPlayer &player,
             IPlayerObject &object,
             ObjectEditResponse response,
             Vector3 offset,
             Vector3 rotation)

WRAP_HANDLER(NodeJSObjectEventHandler, void, onPlayerAttachedObjectEdited, 4, {
    args[0] = EntityToJS<IPlayer>(player, context);
    args[1] = IntToJS<int>(index, context);
    args[2] = BoolToJS(saved, context);
    args[3] = TO_JS_FN(ObjectAttachmentSlotData)(data, context);
}, return, return, IPlayer &player, int index, bool saved, const ObjectAttachmentSlotData &data)

WRAP_BASIC_CODE(IObjectEventDispatcher, addEventHandler, WRAP_ADD_EVENT_HANDLER(NodeJSObjectEventHandler))

WRAP_BASIC_CODE(IObjectEventDispatcher, hasEventHandler, WRAP_HAS_EVENT_HANDLER(NodeJSObjectEventHandler))

WRAP_BASIC_CODE(IObjectEventDispatcher, removeEventHandler, WRAP_REMOVE_EVENT_HANDLER(NodeJSObjectEventHandler))

WRAP_BASIC_CALL_RETURN(IObjectEventDispatcher, count, (size_t, UIntToJS))

EventDispatcherHandleStorage *WrapObjectEventDispatcher(IEventDispatcher<ObjectEventHandler> *dispatcher,
                                                        v8::Local<v8::Context> context) {
    v8::HandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(dispatcher, context, WRAPPED_METHODS(IObjectEventDispatcher));

    return new EventDispatcherHandleStorage(context->GetIsolate(), dispatcherHandle);
}