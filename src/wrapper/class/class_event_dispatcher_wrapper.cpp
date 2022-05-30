#include <utility>

#include "class_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/entity.hpp"
#include "class_event_dispatcher_wrapper.hpp"

WRAP_BASIC(IClassEventDispatcher)
WRAP_HANDLER_BASIC(ClassEventHandler, NodeJSClassEventHandler)

WRAP_HANDLER(NodeJSClassEventHandler, bool, onPlayerRequestClass, 2, {
    args[0] = EntityToJS<IPlayer>(player, context);
    args[1] = UIntToJS<unsigned int>(classId, context);
}, return JSToBool(cbReturnedValue, context), return true, IPlayer &player, unsigned int classId)

WRAP_BASIC_CODE(IClassEventDispatcher, addEventHandler, WRAP_ADD_EVENT_HANDLER(NodeJSClassEventHandler))

WRAP_BASIC_CODE(IClassEventDispatcher, hasEventHandler, WRAP_HAS_EVENT_HANDLER(NodeJSClassEventHandler))

WRAP_BASIC_CODE(IClassEventDispatcher, removeEventHandler, WRAP_REMOVE_EVENT_HANDLER(NodeJSClassEventHandler))

WRAP_BASIC_CALL_RETURN(IClassEventDispatcher, count, (size_t, UIntToJS))

EventDispatcherHandleStorage *WrapClassEventDispatcher(IEventDispatcher<ClassEventHandler> *dispatcher,
                                                       v8::Local<v8::Context> context) {
    v8::HandleScope hs(context->GetIsolate());

    auto dispatcherHandle = InterfaceToObject(dispatcher, context, WRAPPED_METHODS(IClassEventDispatcher));

    return new EventDispatcherHandleStorage(context->GetIsolate(), dispatcherHandle);
}