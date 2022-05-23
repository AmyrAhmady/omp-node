#pragma once

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

#define WRAP_BASIC_CALL_RETURN(ExternalType, getFunction, ConversionToJSFunction, ...) \
    namespace wrapper##_##ExternalType { \
        void getFunction(const v8::FunctionCallbackInfo<v8::Value> &info) { \
            ENTER_FUNCTION_CALLBACK(info); \
            auto external = GetContextExternalPointer<ExternalType>(info); \
            if (external == nullptr) { \
                return; \
            } \
            int argn = 0; \
            auto value = external->getFunction(__VA_ARGS__); \
            auto valueHandle = ConversionToJSFunction(value, context); \
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
            ENTER_FUNCTION_CALLBACK(info); \
            auto external = GetContextExternalPointer<ExternalType>(info); \
            if (external == nullptr) { \
                return; \
            } \
            int argn = 0; \
            external->setFunction(__VA_ARGS__); \
        } \
        AddObjectMethod AddObjectMethod##_##setFunction(#setFunction, setFunction); \
    }