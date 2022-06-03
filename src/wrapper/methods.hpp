#pragma once
#include "../converter/for_each_n.hpp"
#include "../converter/for_each_n_join.hpp"
#include "../converter/find_function.hpp"

#define CONSTRUCTOR_DECLARE_PARAM(ExternalType) v8::Local<v8::FunctionTemplate> constructorOf##ExternalType
#define CONSTRUCTOR_INHERIT(ExternalType) constructorTemplate->Inherit(constructorOf##ExternalType);

/// WITH CONSTRUCTOR
#define WRAP_BASIC_DECLARE_WITH_CONSTRUCTOR(ExternalType) \
    namespace wrapper##_##ExternalType { \
        v8::Local<v8::FunctionTemplate> Wrapped_CreateConstructorTemplate(v8::Isolate *isolate); \
    }

#define WRAP_BASIC_DECLARE_WITH_CONSTRUCTOR_INHERIT(ExternalType, ...) \
    namespace wrapper##_##ExternalType { \
        v8::Local<v8::FunctionTemplate> Wrapped_CreateConstructorTemplate(v8::Isolate *isolate, FOR_EACH(CONSTRUCTOR_DECLARE_PARAM, ##__VA_ARGS__)); \
    }

#define WRAP_BASIC_WITH_CONSTRUCTOR(ExternalType) \
    WRAP_BASIC(ExternalType) \
    namespace wrapper##_##ExternalType { \
        v8::Local<v8::FunctionTemplate> Wrapped_CreateConstructorTemplate(v8::Isolate *isolate) { \
            auto constructorTemplate = CreateConstructorTemplate<ExternalType>(isolate, WRAPPED_METHODS(ExternalType)); \
            return constructorTemplate; \
        } \
    }

#define WRAP_BASIC_WITH_CONSTRUCTOR_INHERIT(ExternalType, ...) \
    WRAP_BASIC(ExternalType) \
    namespace wrapper##_##ExternalType { \
        v8::Local<v8::FunctionTemplate> Wrapped_CreateConstructorTemplate(v8::Isolate *isolate, FOR_EACH(CONSTRUCTOR_DECLARE_PARAM, ##__VA_ARGS__)) { \
            auto constructorTemplate = CreateConstructorTemplate<ExternalType>(isolate, WRAPPED_METHODS(ExternalType));                                 \
            FOR_EACH(CONSTRUCTOR_INHERIT, ##__VA_ARGS__)                 \
            return constructorTemplate; \
        } \
    }

#define CREATE_INSTANCE(ExternalType, external, context) CreateInstance(external, context->Global()->Get(context, v8::String::NewFromUtf8(context->GetIsolate(), #ExternalType).ToLocalChecked()).ToLocalChecked().As<v8::Function>(), context)

/// BASIC

#define WRAP_BASIC(ExternalType) \
    namespace wrapper##_##ExternalType { \
        ObjectMethods methods; \
        struct AddObjectMethod { \
            AddObjectMethod(std::string name, v8::FunctionCallback cb) { \
                methods.push_back({ name, cb }); \
            } \
        }; \
    }

#define WRAPPED_METHODS(ExternalType) wrapper##_##ExternalType::methods

#define CALL(MACRO, ARGS) MACRO ARGS

/// COMMON CALL UTILS

#define ARG_TYPE(Type, Fn, Name, ...) Type
#define ARG_FN(Type, Fn, Name, ...) Fn
#define ARG_NAME(Type, Fn, Name, ...) Name
#define ARG_DEFAULT(Type, Fn, Name, ...) , ##__VA_ARGS__

#define CALL_FN(Fn, infoParam, context, ...) Fn(infoParam, context, ##__VA_ARGS__)

#define DEFINE_ARG(N, CURRENT, ArgInfo) \
    CALL(ARG_TYPE, ArgInfo) CALL(ARG_NAME, ArgInfo) = CALL_FN(CALL(ARG_FN, ArgInfo), info[N - CURRENT], context CALL(ARG_DEFAULT, ArgInfo)); \
    if (tryCatch.HasCaught()) { \
        tryCatch.ReThrow(); \
        return; \
    }

#define USE_ARG(N, CURRENT, ArgInfo) CALL(ARG_NAME, ArgInfo)

#define RETURN_VALUE_TYPE(Type, Fn) Type
#define RETURN_VALUE_FN(Type, Fn) Fn

/// BASIC COMMON

#define WRAP_BASIC_CODE(ExternalType, functionName, Code) \
    namespace wrapper##_##ExternalType { \
        void functionName(const v8::FunctionCallbackInfo<v8::Value> &info) { \
            ENTER_FUNCTION_CALLBACK(info) \
            Code                                          \
        }                                                  \
        AddObjectMethod AddObjectMethod##_##functionName(#functionName, functionName); \
    }

/// BASIC OVERLOADED

#define HANDLE_OVERLOAD_RETURN_(functionName, Condition, ReturnValueInfo, ...) \
    if (Condition) { \
        v8::TryCatch tryCatch(isolate); \
        FOR_EACH_N(DEFINE_ARG, ##__VA_ARGS__) \
        CALL(RETURN_VALUE_TYPE, ReturnValueInfo) value = external->functionName(FOR_EACH_N_JOIN(USE_ARG, ##__VA_ARGS__)); \
        auto valueHandle = CALL(RETURN_VALUE_FN, ReturnValueInfo)(value, context); \
        info.GetReturnValue().Set(valueHandle); \
        return; \
    }

#define HANDLE_OVERLOAD_RETURN(Args) HANDLE_OVERLOAD_RETURN_ Args

#define WRAP_BASIC_CALL_RETURN_OVERLOAD(ExternalType, functionName, ...) \
    WRAP_BASIC_CODE(ExternalType, functionName, { \
        auto external = GetContextExternalPointer<ExternalType>(info); \
        if (external == nullptr) { \
            return; \
        } \
        FOR_EACH(HANDLE_OVERLOAD_RETURN, ##__VA_ARGS__) \
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "Wrong parameter type").ToLocalChecked())); \
    })

#define HANDLE_OVERLOAD_(functionName, Condition, ...) \
    if (Condition) { \
        v8::TryCatch tryCatch(isolate); \
        FOR_EACH_N(DEFINE_ARG, ##__VA_ARGS__) \
        external->functionName(FOR_EACH_N_JOIN(USE_ARG, ##__VA_ARGS__)); \
        return; \
    }

#define HANDLE_OVERLOAD(Args) HANDLE_OVERLOAD_ Args

#define WRAP_BASIC_CALL_OVERLOAD(ExternalType, functionName, ...) \
    WRAP_BASIC_CODE(ExternalType, functionName, { \
        auto external = GetContextExternalPointer<ExternalType>(info); \
        if (external == nullptr) { \
            return; \
        } \
        FOR_EACH(HANDLE_OVERLOAD, ##__VA_ARGS__) \
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "Wrong parameter type").ToLocalChecked())); \
    })

/// POLYMORPHIC

#define WRAP_POLYMORPHIC_BASIC_CODE(ExternalType, functionName, Code) \
    WRAP_BASIC_CODE(ExternalType, functionName, { \
        auto externalType = GetValueInterfaceType(info.This(), context); \
        Code \
    })

#define POLYMORPHIC_BASIC_CALL_RETURN(ExternalType, functionName, ReturnValueInfo, ...) \
    if (externalType == typeid(ExternalType).name()) { \
        auto external = GetContextExternalPointer<ExternalType>(info); \
        if (external == nullptr) { \
            return; \
        } \
        v8::TryCatch tryCatch(isolate); \
        FOR_EACH_N(DEFINE_ARG, ##__VA_ARGS__) \
        CALL(RETURN_VALUE_TYPE, ReturnValueInfo) value = external->functionName(FOR_EACH_N_JOIN(USE_ARG, ##__VA_ARGS__)); \
        auto valueHandle = CALL(RETURN_VALUE_FN, ReturnValueInfo)(value, context); \
        info.GetReturnValue().Set(valueHandle);                                                     \
        return;                                                                                                \
    }

#define POLYMORPHIC_BASIC_CALL(ExternalType, functionName, ...) \
    if (externalType == typeid(ExternalType).name()) { \
        auto external = GetContextExternalPointer<ExternalType>(info); \
        if (external == nullptr) { \
            return; \
        } \
        v8::TryCatch tryCatch(isolate); \
        FOR_EACH_N(DEFINE_ARG, ##__VA_ARGS__) \
        external->functionName(FOR_EACH_N_JOIN(USE_ARG, ##__VA_ARGS__)); \
        return;                                                                 \
    }


/// BASIC

#define WRAP_BASIC_CALL_RETURN(ExternalType, functionName, ReturnValueInfo, ...) \
    WRAP_BASIC_CODE(ExternalType, functionName, { \
        auto external = GetContextExternalPointer<ExternalType>(info); \
        if (external == nullptr) { \
            return; \
        } \
        v8::TryCatch tryCatch(isolate); \
        FOR_EACH_N(DEFINE_ARG, ##__VA_ARGS__) \
        CALL(RETURN_VALUE_TYPE, ReturnValueInfo) value = external->functionName(FOR_EACH_N_JOIN(USE_ARG, ##__VA_ARGS__)); \
        auto valueHandle = CALL(RETURN_VALUE_FN, ReturnValueInfo)(value, context); \
        info.GetReturnValue().Set(valueHandle); \
    })

#define WRAP_BASIC_CALL(ExternalType, functionName, ...) \
    WRAP_BASIC_CODE(ExternalType, functionName, { \
        auto external = GetContextExternalPointer<ExternalType>(info); \
        if (external == nullptr) { \
            return; \
        } \
        v8::TryCatch tryCatch(isolate); \
        FOR_EACH_N(DEFINE_ARG, ##__VA_ARGS__) \
        external->functionName(FOR_EACH_N_JOIN(USE_ARG, ##__VA_ARGS__)); \
    })

#define WRAP_HANDLE_STORAGE_GET(ExternalType, functionName) \
    WRAP_BASIC_CODE(ExternalType, functionName, { \
        auto external = GetContextExternalPointer<ExternalType>(info); \
        if (external == nullptr) { \
            return; \
        } \
        auto value = &external->functionName(); \
        auto valueHandle = GetHandleStorageExtension(value)->get(); \
        info.GetReturnValue().Set(valueHandle); \
    })

/// LOCAL EXTENSION STORAGE GET

#define WRAP_LOCAL_EXT_HANDLE_STORAGE_GET(ExternalType, functionName, ExtensionType) \
    WRAP_BASIC_CODE(ExternalType, functionName, { \
        auto external = GetContextExternalPointer<ExternalType>(info); \
        if (external == nullptr) { \
            return; \
        } \
        auto storageExtension = queryExtension<ExtensionType>(external); \
        auto handle = storageExtension->get(); \
        info.GetReturnValue().Set(handle); \
    })

#define WRAP_LAZILY_GET_EXTENSION_HANDLE(ExternalType, functionName, StorageExtensionType, ExtensionType, WrapExtensionFn) \
    WRAP_BASIC_CODE(ExternalType, functionName, { \
        auto external = GetContextExternalPointer<ExternalType>(info); \
        if (external == nullptr) { \
            return; \
        } \
        auto storageExtension = queryExtension<StorageExtensionType>(external); \
        if (storageExtension == nullptr) { \
            { \
                auto nativeExtension = queryExtension<ExtensionType>(external); \
                if (nativeExtension == nullptr) { \
                    isolate->ThrowException(v8::Exception::ReferenceError(v8::String::NewFromUtf8(isolate, #ExtensionType " extension is not connected").ToLocalChecked())); \
                    return; \
                } \
                auto handleStorageExtensions = WrapExtensionFn(external, nativeExtension, context); \
                for (auto handleStorageExt: handleStorageExtensions) { \
                    external->addExtension(handleStorageExt, true); \
                } \
            } \
            storageExtension = queryExtension<StorageExtensionType>(external); \
            if (storageExtension == nullptr) { \
                return; \
            } \
        } \
        auto handle = storageExtension->get(); \
        info.GetReturnValue().Set(handle); \
    })

/// EXTENSION BASIC CALL

#define WRAP_EXT_BASIC_CALL_RETURN(ExternalType, ExtensionType, functionName, ReturnValueInfo, ...) \
    WRAP_BASIC_CODE(ExternalType, functionName, { \
        auto external = GetContextExternalPointer<ExternalType>(info); \
        if (external == nullptr) { \
            return; \
        } \
        v8::TryCatch tryCatch(isolate); \
        auto extension = queryExtension<ExtensionType>(external); \
        if (extension == nullptr) { \
            info.GetIsolate()->ThrowException(v8::Exception::ReferenceError(v8::String::NewFromUtf8(isolate, #ExtensionType " extension is not connected").ToLocalChecked())); \
            return; \
        }\
        FOR_EACH_N(DEFINE_ARG, ##__VA_ARGS__) \
        CALL(RETURN_VALUE_TYPE, ReturnValueInfo) value = extension->functionName(FOR_EACH_N_JOIN(USE_ARG, ##__VA_ARGS__)); \
        auto valueHandle = CALL(RETURN_VALUE_FN, ReturnValueInfo)(value, context); \
        info.GetReturnValue().Set(valueHandle); \
    })

#define WRAP_EXT_BASIC_CALL(ExternalType, ExtensionType, functionName, ...) \
    WRAP_BASIC_CODE(ExternalType, functionName, { \
        auto external = GetContextExternalPointer<ExternalType>(info); \
        if (external == nullptr) { \
            return; \
        } \
        v8::TryCatch tryCatch(isolate); \
        auto extension = queryExtension<ExtensionType>(external); \
        if (extension == nullptr) { \
            info.GetIsolate()->ThrowException(v8::Exception::ReferenceError(v8::String::NewFromUtf8(isolate, #ExtensionType " extension is not connected").ToLocalChecked())); \
            return; \
        }\
        FOR_EACH_N(DEFINE_ARG, ##__VA_ARGS__) \
        extension->functionName(FOR_EACH_N_JOIN(USE_ARG, ##__VA_ARGS__)); \
    })