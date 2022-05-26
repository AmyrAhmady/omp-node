#pragma once
#include "v8.h"

#define WRAP_HANDLER_BASIC(FullType, TypeAlias) \
    namespace handler_wrapper_##_##TypeAlias {  \
        typedef FullType HandlerType;                                        \
        typedef NodeJSEventHandler<FullType> TypeAlias; \
        using HandlerCreatorFunction = TypeAlias* (*)(Impl::String, v8::Local<v8::Function>); \
        typedef FlatHashMap<std::string, HandlerCreatorFunction> HandlerGenerators; \
        HandlerGenerators handlerGenerators; \
        struct AddObjectHandler { \
            AddObjectHandler(std::string name, HandlerCreatorFunction generator) { \
                handlerGenerators.insert({ name, generator }); \
            } \
        }; \
        HandlerCreatorFunction GetHandler(std::string name) { \
            auto fnIt = handlerGenerators.find(name); \
            if (fnIt == handlerGenerators.end()) { \
                return nullptr; \
            } \
            return fnIt->second; \
        } \
        FlatPtrHashSet<TypeAlias> eventHandlers; \
    }

#define WRAP_HANDLER(Type, returnType, handlerFunctionName, argsCount, codeBlock, returnValue, ...) \
    namespace handler_wrapper_##_##Type { \
        struct H##_##handlerFunctionName : Type { \
            H##_##handlerFunctionName(Impl::String _event, v8::Local<v8::Function> _handler) : Type( \
                std::move(_event), \
                _handler) { \
            } \
            returnType handlerFunctionName(__VA_ARGS__) override { \
                ENTER_HANDLER(isolate, handler) \
                v8::Local<v8::Value> args[argsCount]; \
                codeBlock \
                auto cbReturnedValue = func->Call(context, context->Global(), argsCount, args).ToLocalChecked(); \
                returnValue; \
            } \
        }; \
        Type *generate_handler##_##handlerFunctionName(Impl::String _event, v8::Local<v8::Function> _handler) { \
            return new H##_##handlerFunctionName(_event, _handler); \
        }\
        AddObjectHandler AddObjectHandler##_##handlerFunctionName(#handlerFunctionName, generate_handler##_##handlerFunctionName); \
    }

#define WRAP_ADD_EVENT_HANDLER(Type) { \
    ENTER_FUNCTION_CALLBACK(info) \
    auto dispatcher = GetContextExternalPointer<IEventDispatcher<handler_wrapper_##_##Type::HandlerType>>(info); \
    auto event = JSToString(info[0], context); \
    auto handler = info[1].As<v8::Function>(); \
    if (!handler->IsFunction()) { \
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, \
                                                                                 "A function is required").ToLocalChecked())); \
        return; \
    } \
    auto handlerObjGenerator = WRAPPED_HANDLER(Type, event); \
    if (handlerObjGenerator == nullptr) { \
        info.GetReturnValue().Set(false); \
        return; \
    } \
    auto handlerObj = handlerObjGenerator(event, handler); \
    auto result = dispatcher->addEventHandler(handlerObj, EventPriority_Lowest); \
    if (result) { \
        WRAPPED_HANDLERS(Type).emplace(handlerObj); \
    } else { \
        delete handlerObj; \
    } \
    info.GetReturnValue().Set(result); \
}

#define WRAP_HAS_EVENT_HANDLER(Type) { \
    ENTER_FUNCTION_CALLBACK(info) \
    auto dispatcher = GetContextExternalPointer<IEventDispatcher<handler_wrapper_##_##Type::HandlerType>>(info); \
    auto event = JSToString(info[0], context); \
    auto handler = info[1].As<v8::Function>(); \
    if (!handler->IsFunction()) { \
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, \
                                                                                 "A function is required").ToLocalChecked())); \
        return; \
    } \
    std::underlying_type_t<EventPriority> priority; \
    for (auto handlerObj: WRAPPED_HANDLERS(Type)) { \
        if (handlerObj->getEvent() == event && handlerObj->getHandler() == handler) { \
            bool result = dispatcher->hasEventHandler(handlerObj, priority);                                     \
            info.GetReturnValue().Set(result); \
            return; \
        } \
    } \
    info.GetReturnValue().Set(false); \
}

#define WRAP_REMOVE_EVENT_HANDLER(Type) { \
    ENTER_FUNCTION_CALLBACK(info) \
    auto dispatcher = GetContextExternalPointer<IEventDispatcher<handler_wrapper_##_##Type::HandlerType>>(info); \
    auto event = JSToString(info[0], context); \
    auto handler = info[1].As<v8::Function>(); \
    if (!handler->IsFunction()) { \
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, \
                                                                                 "A function is required").ToLocalChecked())); \
        return; \
    } \
    for (auto handlerObj: WRAPPED_HANDLERS(Type)) { \
        if (handlerObj->getEvent() == event && handlerObj->getHandler() == handler) { \
            auto result = dispatcher->removeEventHandler(handlerObj); \
            info.GetReturnValue().Set(result); \
            if (result) { \
                WRAPPED_HANDLERS(Type).erase(handlerObj);                                                        \
                delete handlerObj;                              \
            } \
            return; \
        } \
    } \
    info.GetReturnValue().Set(false); \
}

#define WRAPPED_HANDLERS(Type) handler_wrapper_##_##Type::eventHandlers
#define WRAPPED_HANDLER(Type, name) handler_wrapper_##_##Type::GetHandler(name)

template<class EventHandlerBase>
struct NodeJSEventHandler : EventHandlerBase {
    Impl::String event;
    v8::Isolate *isolate;
    v8::UniquePersistent<v8::Function> handler;

    NodeJSEventHandler(Impl::String _event, v8::Local<v8::Function> _handler) {
        event = std::move(_event);
        isolate = _handler->GetIsolate();
        handler = v8::UniquePersistent<v8::Function>(isolate, _handler);
    }

    virtual ~NodeJSEventHandler() {
        isolate = nullptr;
        handler.Reset();
        L_DEBUG << "~NodeJSEventHandler";
    }

public:
    Impl::String getEvent() const {
        return event;
    }

    v8::Local<v8::Value> getHandler() {
        v8::EscapableHandleScope hs(isolate);

        return hs.Escape(handler.Get(isolate));
    }
};
