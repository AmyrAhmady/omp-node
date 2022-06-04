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
            auto constructorTemplate = CreateConstructorTemplate<ExternalType>(isolate, WRAPPED_METHODS(ExternalType), WRAPPED_ACCESSORS(ExternalType)); \
            return constructorTemplate; \
        } \
    }

#define WRAP_BASIC_WITH_CONSTRUCTOR_CALLBACK(ExternalType, Callback) \
    WRAP_BASIC(ExternalType) \
    namespace wrapper##_##ExternalType { \
        v8::Local<v8::FunctionTemplate> Wrapped_CreateConstructorTemplate(v8::Isolate *isolate) { \
            auto constructorTemplate = CreateConstructorTemplate<ExternalType>(isolate, WRAPPED_METHODS(ExternalType), WRAPPED_ACCESSORS(ExternalType), Callback); \
            return constructorTemplate; \
        } \
    }

#define WRAP_BASIC_WITH_CONSTRUCTOR_NO_TYPE(ExternalType) \
    WRAP_BASIC(ExternalType) \
    namespace wrapper##_##ExternalType { \
        v8::Local<v8::FunctionTemplate> Wrapped_CreateConstructorTemplate(v8::Isolate *isolate) { \
            auto constructorTemplate = CreateConstructorTemplate<void>(isolate, WRAPPED_METHODS(ExternalType), WRAPPED_ACCESSORS(ExternalType)); \
            return constructorTemplate; \
        } \
    }

#define WRAP_BASIC_WITH_CONSTRUCTOR_INHERIT(ExternalType, ...) \
    WRAP_BASIC(ExternalType) \
    namespace wrapper##_##ExternalType { \
        v8::Local<v8::FunctionTemplate> Wrapped_CreateConstructorTemplate(v8::Isolate *isolate, FOR_EACH(CONSTRUCTOR_DECLARE_PARAM, ##__VA_ARGS__)) { \
            auto constructorTemplate = CreateConstructorTemplate<ExternalType>(isolate, WRAPPED_METHODS(ExternalType), WRAPPED_ACCESSORS(ExternalType));                                 \
            FOR_EACH(CONSTRUCTOR_INHERIT, ##__VA_ARGS__)                 \
            return constructorTemplate; \
        } \
    }

#define WRAP_BASIC_WITH_CONSTRUCTOR_INHERIT_NO_TYPE(ExternalType, ...) \
    WRAP_BASIC(ExternalType) \
    namespace wrapper##_##ExternalType { \
        v8::Local<v8::FunctionTemplate> Wrapped_CreateConstructorTemplate(v8::Isolate *isolate, FOR_EACH(CONSTRUCTOR_DECLARE_PARAM, ##__VA_ARGS__)) { \
            auto constructorTemplate = CreateConstructorTemplate<void>(isolate, WRAPPED_METHODS(ExternalType), WRAPPED_ACCESSORS(ExternalType));                                 \
            FOR_EACH(CONSTRUCTOR_INHERIT, ##__VA_ARGS__)                 \
            return constructorTemplate; \
        } \
    }

#define CREATE_INSTANCE(ExternalType, external, context) CreateInstance(external, context->Global()->Get(context, v8::String::NewFromUtf8(context->GetIsolate(), #ExternalType).ToLocalChecked()).ToLocalChecked().As<v8::Function>(), context)
#define CREATE_INSTANCE_CLOSEST(ExternalType, external, context, closest) CreateInstance(external, context->Global()->Get(context, v8::String::NewFromUtf8(context->GetIsolate(), #ExternalType).ToLocalChecked()).ToLocalChecked().As<v8::Function>(), context, closest)

/// BASIC

#define WRAP_BASIC(ExternalType) \
    namespace wrapper##_##ExternalType { \
        ObjectMethods methods;   \
        ObjectAccessors accessors; \
        struct AddObjectMethod { \
            AddObjectMethod(std::string name, v8::FunctionCallback cb) { \
                methods.push_back({ name, cb }); \
            } \
        };                       \
        struct AddObjectAccessor { \
            AddObjectAccessor(std::string name, v8::FunctionCallback getter, v8::FunctionCallback setter) { \
                accessors.push_back({ name, getter, setter }); \
            } \
        }; \
    }

#define WRAPPED_METHODS(ExternalType) wrapper##_##ExternalType::methods
#define WRAPPED_ACCESSORS(ExternalType) wrapper##_##ExternalType::accessors

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

/// ACCESSOR

#define WRAP_ACCESSOR_CODE(ExternalType, propertyName, Getter, Setter) \
    namespace wrapper##_##ExternalType { \
        void Get##_##propertyName(const v8::FunctionCallbackInfo<v8::Value> &info) { \
            ENTER_FUNCTION_CALLBACK(info) \
            Getter                                          \
        } \
        void Set##_##propertyName(const v8::FunctionCallbackInfo<v8::Value> &info) { \
            ENTER_FUNCTION_CALLBACK(info) \
            Setter                                          \
        }                                                  \
        AddObjectAccessor AddObjectAccessor##_##propertyName(#propertyName, Get##_##propertyName, Set##_##propertyName); \
    }

#define WRAP_ACCESSOR(ExternalType, propertyName, path, GetterInfo, SetterInfo) \
    WRAP_ACCESSOR_CODE(ExternalType, propertyName, {                                    \
        auto external = GetContextExternalPointer<ExternalType>(info); \
        if (external == nullptr) { \
            return; \
        } \
        v8::TryCatch tryCatch(isolate); \
        CALL(RETURN_VALUE_TYPE, GetterInfo) value = external->path; \
        auto valueHandle = CALL(RETURN_VALUE_FN, GetterInfo)(value, context); \
        info.GetReturnValue().Set(valueHandle); \
    }, {                                                                                  \
        auto external = GetContextExternalPointer<ExternalType>(info); \
        if (external == nullptr) { \
            return; \
        } \
        v8::TryCatch tryCatch(isolate);                                         \
        DEFINE_ARG(1, 1, SetterInfo);                                           \
        external->path = USE_ARG(1, 1, SetterInfo); \
    })
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

#define DEFINE_ARG_RETURN_TRUE(N, CURRENT, ArgInfo) \
    CALL(ARG_TYPE, ArgInfo) CALL(ARG_NAME, ArgInfo) = CALL_FN(CALL(ARG_FN, ArgInfo), info[N - CURRENT], context CALL(ARG_DEFAULT, ArgInfo)); \
    if (tryCatch.HasCaught()) { \
        tryCatch.ReThrow(); \
        return true; \
    }

#define CALL_SUB_FN(Type) if (fn<Type>(isolate, context, externalType, info)) return;
#define CALL_SUB_FNS_(...) FOR_EACH(CALL_SUB_FN, ##__VA_ARGS__)
#define CALL_SUB_FNS(Args) CALL_SUB_FNS_ Args

#define WRAP_POLYMORPHIC_BASIC_CODE(ExternalType, AllTypes, functionName, Code) \
    namespace wrapper##_##ExternalType { \
        namespace wrapper##_##ExternalType##_##functionName { \
            template<class Interface> \
            bool fn(v8::Isolate *isolate, v8::Local<v8::Context> context, const std::string &externalType, const v8::FunctionCallbackInfo<v8::Value> &info) { \
                if (externalType == typeid(Interface).name()) { \
                    auto external = GetContextExternalPointer<Interface>(info); \
                    if (external == nullptr) { \
                        return true; \
                    } \
                    Code \
                    return true; \
                } \
                return false; \
            } \
            void functionName(const v8::FunctionCallbackInfo<v8::Value> &info) { \
                ENTER_FUNCTION_CALLBACK(info) \
                auto externalType = GetValueInterfaceType(info.This(), context);\
                CALL_SUB_FNS(AllTypes) \
            } \
            AddObjectMethod AddObjectMethod##_##functionName(#functionName, functionName); \
        }\
    }



#define WRAP_POLYMORPHIC_BASIC_CALL_RETURN(ExternalType, AllTypes, functionName, ReturnValueInfo, ...) \
    WRAP_POLYMORPHIC_BASIC_CODE(ExternalType, AllTypes, functionName, { \
        v8::TryCatch tryCatch(isolate); \
        FOR_EACH_N(DEFINE_ARG_RETURN_TRUE, ##__VA_ARGS__) \
        CALL(RETURN_VALUE_TYPE, ReturnValueInfo) value = external->functionName(FOR_EACH_N_JOIN(USE_ARG, ##__VA_ARGS__)); \
        auto valueHandle = CALL(RETURN_VALUE_FN, ReturnValueInfo)(value, context); \
        info.GetReturnValue().Set(valueHandle); \
    })

#define WRAP_POLYMORPHIC_BASIC_CALL(ExternalType, AllTypes, functionName, ...) \
    WRAP_POLYMORPHIC_BASIC_CODE(ExternalType, AllTypes, functionName, {        \
        v8::TryCatch tryCatch(isolate); \
        FOR_EACH_N(DEFINE_ARG_RETURN_TRUE, ##__VA_ARGS__) \
        external->functionName(FOR_EACH_N_JOIN(USE_ARG, ##__VA_ARGS__)); \
    })

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