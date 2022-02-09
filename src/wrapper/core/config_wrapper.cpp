#include "config_wrapper.hpp"
#include "../../logger.hpp"

void getString(const v8::FunctionCallbackInfo<v8::Value> &info) {
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

    auto resultHandle = StringViewToJS(result, isolate);

    info.GetReturnValue().Set(resultHandle);
}

void getInt(const v8::FunctionCallbackInfo<v8::Value> &info) {
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

    auto resultHandle = IntToJS(*result, isolate);

    info.GetReturnValue().Set(resultHandle);
}

void getFloat(const v8::FunctionCallbackInfo<v8::Value> &info) {
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

    auto resultHandle = FloatToJS(*result, isolate);

    info.GetReturnValue().Set(resultHandle);
}

void getStrings(const v8::FunctionCallbackInfo<v8::Value> &info) {
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
        values[i] = StringViewToJS(strings[i], isolate);
    }

    auto arrayHandle = v8::Array::New(isolate, values, count);

    info.GetReturnValue().Set(arrayHandle);
}

void getStringsCount(const v8::FunctionCallbackInfo<v8::Value> &info) {
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

    auto countHandle = UIntToJS(count, isolate);

    info.GetReturnValue().Set(countHandle);
}

void getType(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto config = GetContextExternalPointer<IConfig>(info);

    auto key = JSToString(info[0], context);

    auto type = config->getType(key);

    auto typeHandle = IntToJS(type, isolate);

    info.GetReturnValue().Set(typeHandle);
}

void get(const v8::FunctionCallbackInfo<v8::Value> &info) {
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
}

void getBansCount(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto config = GetContextExternalPointer<IConfig>(info);

    auto count = config->getBansCount();

    auto countHandle = UIntToJS(count, isolate);

    info.GetReturnValue().Set(countHandle);
}

void getBan(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto config = GetContextExternalPointer<IConfig>(info);

    auto index = JSToInt(info[0], context);

    // todo: add checking bans count

    auto ban = config->getBan(index);

    auto banHandle = BanEntryToJS(ban, context);

    info.GetReturnValue().Set(banHandle);
}

void addBan(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto config = GetContextExternalPointer<IConfig>(info);

    auto banEntry = JSToBanEntry(info[0], context);

    config->addBan(banEntry);
}

void removeBan(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto config = GetContextExternalPointer<IConfig>(info);

    auto index = JSToInt(info[0], context);

    // todo: add checking bans count

    config->removeBan(index);
}

void writeBans(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto config = GetContextExternalPointer<IConfig>(info);

    config->writeBans();
}

void WrapConfig(HandleStorage &storage, IConfig *config, v8::Local<v8::Context> context) {
    ObjectMethods methods = {{"getString",       getString},
                             {"getInt",          getInt},
                             {"getFloat",        getFloat},
                             {"getStrings",      getStrings},
                             {"getStringsCount", getStringsCount},
                             {"getType",         getType},
                             {"get",             get},
                             {"getBansCount",    getBansCount},
                             {"getBan",          getBan},
                             {"addBan",          addBan},
                             {"removeBan",       removeBan},
                             {"writeBans",       writeBans},
    };
    auto configHandle = InterfaceToObject(storage, config, context, methods);

    storage.set(config, new v8::UniquePersistent<v8::Value>(context->GetIsolate(), configHandle));
}
