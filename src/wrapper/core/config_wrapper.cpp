#include "config_wrapper.hpp"
#include "../../logger.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/network.hpp"

WRAP_BASIC(IConfig)

WRAP_BASIC_CODE(IConfig, getString, {
    ENTER_FUNCTION_CALLBACK(info)
    auto config = GetContextExternalPointer<IConfig>(info);
    auto key = JSToString(info[0], context);
    auto type = config->getType(key);
    if (type != ConfigOptionType::ConfigOptionType_String) {
        info.GetIsolate()->ThrowException(v8::Exception::ReferenceError(v8::String::NewFromUtf8(isolate,
                                                                                                "The key doesn't contain a string").ToLocalChecked()));
        return;
    }
    auto result = config->getString(key);
    auto resultHandle = StringViewToJS(result, context);
    info.GetReturnValue().Set(resultHandle);
})
WRAP_BASIC_CODE(IConfig, getInt, {
    ENTER_FUNCTION_CALLBACK(info)
    auto config = GetContextExternalPointer<IConfig>(info);
    auto key = JSToString(info[0], context);
    auto type = config->getType(key);
    if (type != ConfigOptionType::ConfigOptionType_Int) {
        info.GetIsolate()->ThrowException(v8::Exception::ReferenceError(v8::String::NewFromUtf8(isolate,
                                                                                                "The key doesn't contain an integer").ToLocalChecked()));
        return;
    }
    auto result = config->getInt(key);
    auto resultHandle = IntToJS(*result, context);
    info.GetReturnValue().Set(resultHandle);
})
WRAP_BASIC_CODE(IConfig, getFloat, {
    ENTER_FUNCTION_CALLBACK(info)
    auto config = GetContextExternalPointer<IConfig>(info);
    auto key = JSToString(info[0], context);
    auto type = config->getType(key);
    if (type != ConfigOptionType::ConfigOptionType_Float) {
        info.GetIsolate()->ThrowException(v8::Exception::ReferenceError(v8::String::NewFromUtf8(isolate,
                                                                                                "The key doesn't contain a float").ToLocalChecked()));
        return;
    }
    auto result = config->getFloat(key);
    auto resultHandle = FloatToJS(*result, context);
    info.GetReturnValue().Set(resultHandle);
})
WRAP_BASIC_CODE(IConfig, getStrings, {
    ENTER_FUNCTION_CALLBACK(info)
    auto config = GetContextExternalPointer<IConfig>(info);
    auto key = JSToString(info[0], context);
    auto type = config->getType(key);
    if (type != ConfigOptionType::ConfigOptionType_Strings) {
        info.GetIsolate()->ThrowException(v8::Exception::ReferenceError(v8::String::NewFromUtf8(isolate,
                                                                                                "The key doesn't contain a string array").ToLocalChecked()));
        return;
    }
    auto count = config->getStringsCount(key);
    StringView strings[count];
    config->getStrings(key, Span<StringView>(strings, count));
    v8::Local<v8::Value> values[count];
    for (int i = 0; i < count; i++) {
        values[i] = StringViewToJS(strings[i], context);
    }
    auto arrayHandle = v8::Array::New(isolate, values, count);
    info.GetReturnValue().Set(arrayHandle);
})
WRAP_BASIC_CODE(IConfig, getStringsCount, {
    ENTER_FUNCTION_CALLBACK(info)
    auto config = GetContextExternalPointer<IConfig>(info);
    auto key = JSToString(info[0], context);
    auto type = config->getType(key);
    if (type != ConfigOptionType::ConfigOptionType_Strings) {
        info.GetIsolate()->ThrowException(v8::Exception::ReferenceError(v8::String::NewFromUtf8(isolate,
                                                                                                "The key doesn't contain a string array").ToLocalChecked()));
        return;
    }
    auto count = config->getStringsCount(key);
    auto countHandle = UIntToJS(count, context);
    info.GetReturnValue().Set(countHandle);
})
WRAP_BASIC_CODE(IConfig, getType, {
    ENTER_FUNCTION_CALLBACK(info)
    auto config = GetContextExternalPointer<IConfig>(info);
    auto key = JSToString(info[0], context);
    auto type = config->getType(key);
    auto typeHandle = IntToJS(type, context);
    info.GetReturnValue().Set(typeHandle);
})
WRAP_BASIC_CODE(IConfig, get, {
    ENTER_FUNCTION_CALLBACK(info)
    auto config = GetContextExternalPointer<IConfig>(info);
    auto key = JSToString(info[0], context);
    auto type = config->getType(key);
    if (type == ConfigOptionType::ConfigOptionType_String) {
        getString(info);
    } else if (type == ConfigOptionType::ConfigOptionType_Int) {
        getInt(info);
    } else if (type == ConfigOptionType::ConfigOptionType_Float) {
        getFloat(info);
    } else if (type == ConfigOptionType::ConfigOptionType_Strings) {
        getStrings(info);
    } else {
        info.GetIsolate()->ThrowException(v8::Exception::ReferenceError(v8::String::NewFromUtf8(isolate,
                                                                                                "The key doesn't contain a value").ToLocalChecked()));
    }
})
WRAP_BASIC_CALL_RETURN(IConfig, getBansCount, UIntToJS)
WRAP_BASIC_CALL_RETURN(IConfig, getBan, BanEntryToJS, JSToInt(info[0], context))
WRAP_BASIC_CALL(IConfig, addBan, JSToBanEntry(info[0], context))
WRAP_BASIC_CALL(IConfig, removeBan, JSToInt(info[0], context))
WRAP_BASIC_CALL(IConfig, writeBans)

void WrapConfig(IConfig *config, v8::Local<v8::Context> context) {
    auto configHandle = InterfaceToObject(config, context, WRAPPED_METHODS(IConfig));

    config->addExtension(new IHandleStorage(context->GetIsolate(), configHandle), true);
}
