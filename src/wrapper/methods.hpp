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

#define BYPASS_N(N, CURRENT, val) val

#define ARG_TYPE(Type, Fn, Name, ...) Type
#define ARG_FN(Type, Fn, Name, ...) Fn
#define ARG_NAME(Type, Fn, Name, ...) Name
#define ARG_DEFAULT(Type, Fn, Name, ...) , ##__VA_ARGS__

#define CALL_FN(Fn, infoParam, context, ...) Fn(infoParam, context, ##__VA_ARGS__)

#define DEFINE_ARG(N, CURRENT, ArgInfo) \
    CALL(ARG_TYPE, ArgInfo) CALL(ARG_NAME, ArgInfo) = CALL_FN(CALL(ARG_FN, ArgInfo), info[N - CURRENT], context CALL(ARG_DEFAULT, ArgInfo)); \
    if (tryCatch.HasCaught()) {                                         \
        tryCatch.ReThrow(); \
        return;                                                                    \
    }

// arg_##CURRENT##_of_##N
#define USE_ARG(N, CURRENT, ArgInfo) CALL(ARG_NAME, ArgInfo)


#define RETURN_VALUE_TYPE(Type, Fn) Type
#define RETURN_VALUE_FN(Type, Fn) Fn

#define WRAP_BASIC_CALL_RETURN(ExternalType, getFunction, ReturnValueInfo, ...) \
    namespace wrapper##_##ExternalType { \
        void getFunction(const v8::FunctionCallbackInfo<v8::Value> &info) { \
            ENTER_FUNCTION_CALLBACK(info) \
            auto external = GetContextExternalPointer<ExternalType>(info); \
            if (external == nullptr) { \
                return; \
            } \
            v8::TryCatch tryCatch(isolate);                                                           \
            FOR_EACH_N(DEFINE_ARG, ##__VA_ARGS__)                               \
            CALL(RETURN_VALUE_TYPE, ReturnValueInfo) value = external->getFunction(FOR_EACH_N_JOIN(USE_ARG, ##__VA_ARGS__)); \
            auto valueHandle = CALL(RETURN_VALUE_FN, ReturnValueInfo)(value, context); \
            info.GetReturnValue().Set(valueHandle); \
        } \
        AddObjectMethod AddObjectMethod##_##getFunction(#getFunction, getFunction); \
    }

#define WRAP_BASIC_CODE(ExternalType, getFunction, Code) \
    namespace wrapper##_##ExternalType { \
        void getFunction(const v8::FunctionCallbackInfo<v8::Value> &info) Code \
        AddObjectMethod AddObjectMethod##_##getFunction(#getFunction, getFunction); \
    }

#define WRAP_HANDLE_STORAGE_GET(ExternalType, getFunction) \
    namespace wrapper##_##ExternalType { \
        void getFunction(const v8::FunctionCallbackInfo<v8::Value> &info) { \
            ENTER_FUNCTION_CALLBACK(info) \
            auto external = GetContextExternalPointer<ExternalType>(info); \
            if (external == nullptr) { \
                return; \
            } \
            auto value = &external->getFunction(); \
            auto valueHandle = GetHandleStorageExtension(value)->get(); \
            info.GetReturnValue().Set(valueHandle); \
        } \
        AddObjectMethod AddObjectMethod##_##getFunction(#getFunction, getFunction); \
    }

#define WRAP_BASIC_CALL(ExternalType, setFunction, ...) \
    namespace wrapper##_##ExternalType { \
        void setFunction(const v8::FunctionCallbackInfo<v8::Value> &info) { \
            ENTER_FUNCTION_CALLBACK(info) \
            auto external = GetContextExternalPointer<ExternalType>(info); \
            if (external == nullptr) { \
                return; \
            } \
            v8::TryCatch tryCatch(isolate);                                                           \
            FOR_EACH_N(DEFINE_ARG, ##__VA_ARGS__)       \
            external->setFunction(FOR_EACH_N_JOIN(USE_ARG, ##__VA_ARGS__)); \
        } \
        AddObjectMethod AddObjectMethod##_##setFunction(#setFunction, setFunction); \
    }
