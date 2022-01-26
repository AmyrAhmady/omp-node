#include "config_wrapper.hpp"
#include "../../logger.hpp"

void
getInt(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto config = GetContextExternalPointer<IConfig>(info);

    auto key = JSToStringView(info[0], context);

    auto result = config->getInt(key);

    if (result == nullptr) {
        info.GetIsolate()->ThrowException(v8::Exception::ReferenceError(v8::String::NewFromUtf8(isolate,
                                                                                                "The key doesn't contain an integer").ToLocalChecked()));

        return;
    }

    auto resultHandle = v8::Integer::New(isolate, *result);

    info.GetReturnValue().Set(resultHandle);
}

void
WrapConfig(HandleStorage &storage, IConfig *config, v8::Local<v8::Context> context) {
    ObjectMethods methods = {
        {"getInt", getInt}
    };
    auto configHandle = InterfaceToObject(storage, config, context, methods);

    storage.set(config, new v8::UniquePersistent<v8::Value>(context->GetIsolate(), configHandle));
}
