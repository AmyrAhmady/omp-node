#pragma once
#include "v8.h"

#define WRAP_HANDLER_BASIC(FullType, TypeAlias) \
    namespace handler_wrapper_##_##TypeAlias { \
        typedef FullType TypeAlias; \
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

public:
    Impl::String getEvent() const {
        return event;
    }

    v8::Local<v8::Value> getHandler() {
        v8::EscapableHandleScope hs(isolate);

        return hs.Escape(handler.Get(isolate));
    }
};
