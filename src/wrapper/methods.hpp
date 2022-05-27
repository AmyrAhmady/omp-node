#pragma once
#include "../converter/for_each_n.hpp"
#include "../converter/for_each_n_join.hpp"
#include "../converter/find_function.hpp"

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

// arg_##CURRENT##_of_##N
#define USE_ARG(N, CURRENT, ArgInfo) CALL(ARG_NAME, ArgInfo)

#define RETURN_VALUE_TYPE(Type, Fn) Type
#define RETURN_VALUE_FN(Type, Fn) Fn

#define WRAP_BASIC_CALL_RETURN(ExternalType, functionName, ReturnValueInfo, ...) \
    namespace wrapper##_##ExternalType { \
        void functionName(const v8::FunctionCallbackInfo<v8::Value> &info) { \
            ENTER_FUNCTION_CALLBACK(info) \
            auto external = GetContextExternalPointer<ExternalType>(info); \
            if (external == nullptr) { \
                return; \
            } \
            v8::TryCatch tryCatch(isolate); \
            FOR_EACH_N(DEFINE_ARG, ##__VA_ARGS__) \
            CALL(RETURN_VALUE_TYPE, ReturnValueInfo) value = external->functionName(FOR_EACH_N_JOIN(USE_ARG, ##__VA_ARGS__)); \
            auto valueHandle = CALL(RETURN_VALUE_FN, ReturnValueInfo)(value, context); \
            info.GetReturnValue().Set(valueHandle); \
        } \
        AddObjectMethod AddObjectMethod##_##functionName(#functionName, functionName); \
    }

#define WRAP_BASIC_CODE(ExternalType, functionName, Code) \
    namespace wrapper##_##ExternalType { \
        void functionName(const v8::FunctionCallbackInfo<v8::Value> &info) Code \
        AddObjectMethod AddObjectMethod##_##functionName(#functionName, functionName); \
    }

#define WRAP_BASIC_CALL(ExternalType, functionName, ...) \
    namespace wrapper##_##ExternalType { \
        void functionName(const v8::FunctionCallbackInfo<v8::Value> &info) { \
            ENTER_FUNCTION_CALLBACK(info) \
            auto external = GetContextExternalPointer<ExternalType>(info); \
            if (external == nullptr) { \
                return; \
            } \
            v8::TryCatch tryCatch(isolate); \
            FOR_EACH_N(DEFINE_ARG, ##__VA_ARGS__) \
            external->functionName(FOR_EACH_N_JOIN(USE_ARG, ##__VA_ARGS__)); \
        } \
        AddObjectMethod AddObjectMethod##_##functionName(#functionName, functionName); \
    }

#define WRAP_HANDLE_STORAGE_GET(ExternalType, functionName) \
    namespace wrapper##_##ExternalType { \
        void functionName(const v8::FunctionCallbackInfo<v8::Value> &info) { \
            ENTER_FUNCTION_CALLBACK(info) \
            auto external = GetContextExternalPointer<ExternalType>(info); \
            if (external == nullptr) { \
                return; \
            } \
            auto value = &external->functionName(); \
            auto valueHandle = GetHandleStorageExtension(value)->get(); \
            info.GetReturnValue().Set(valueHandle); \
        } \
        AddObjectMethod AddObjectMethod##_##functionName(#functionName, functionName); \
    }

#define WRAP_EXT_BASIC_CALL_RETURN(ExternalType, ExtensionType, functionName, ReturnValueInfo, ...) \
    namespace wrapper##_##ExternalType { \
        void functionName(const v8::FunctionCallbackInfo<v8::Value> &info) { \
            ENTER_FUNCTION_CALLBACK(info) \
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
        } \
        AddObjectMethod AddObjectMethod##_##functionName(#functionName, functionName); \
    }

#define WRAP_EXT_BASIC_CALL(ExternalType, ExtensionType, functionName, ...) \
    namespace wrapper##_##ExternalType { \
        void functionName(const v8::FunctionCallbackInfo<v8::Value> &info) { \
            ENTER_FUNCTION_CALLBACK(info) \
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
            external->functionName(FOR_EACH_N_JOIN(USE_ARG, ##__VA_ARGS__)); \
        } \
        AddObjectMethod AddObjectMethod##_##functionName(#functionName, functionName); \
    }