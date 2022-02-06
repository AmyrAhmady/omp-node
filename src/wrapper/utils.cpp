#include "utils.hpp"

void HandleStorage::setConstructor(StringView key, v8::UniquePersistent<v8::Value> *value) {
    constructorsMap.emplace(key, value);
}

v8::UniquePersistent<v8::Value> *HandleStorage::getConstructor(StringView key) {
    auto pair = constructorsMap.find(key);

    if (pair != constructorsMap.end()) {
        return pair->second;
    }

    return nullptr; // todo: don't return nullptr
}

void HandleStorage::removeConstructor(StringView key) {
    auto value = getConstructor(key);

    if (key != nullptr) {
        delete value;

        constructorsMap.erase(key);
    }
}

HandleStorage::~HandleStorage() {
    for (auto pair: storageMap) {
        delete pair.second;
    }

    for (auto pair: constructorsMap) {
        delete pair.second;
    }
}

float JSToFloat(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return float();
    }

    return static_cast<float>(value->ToNumber(context).ToLocalChecked()->NumberValue(context).ToChecked());
}

int JSToInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return int();
    }

    return static_cast<int>(value->ToInteger(context).ToLocalChecked()->Int32Value(context).ToChecked());
}

#include "../logger.hpp"

StringView JSToStringView(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return StringView();
    }

    return StringView(utils::js_to_cstr(isolate, value));
}

bool JSToBool(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return bool();
    }

    return value->ToBoolean(isolate)->Value();
}

Vector3 JSToVector3(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (!value->IsArray()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An array is required").ToLocalChecked()));
        return Vector3();
    }

    auto xHandle = value.As<v8::Array>()->Get(context, 0);
    auto yHandle = value.As<v8::Array>()->Get(context, 1);
    auto zHandle = value.As<v8::Array>()->Get(context, 2);

    if (xHandle.IsEmpty() || yHandle.IsEmpty() || zHandle.IsEmpty()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An array must contain 3 numbers").ToLocalChecked()));
        return Vector3();
    }

    auto x = JSToFloat(xHandle.ToLocalChecked(), context);
    auto y = JSToFloat(yHandle.ToLocalChecked(), context);
    auto z = JSToFloat(zHandle.ToLocalChecked(), context);

    return {
        x,
        y,
        z
    };
}

BanEntry JSToBanEntry(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (!value->IsObject()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An object is required").ToLocalChecked()));
        return BanEntry("");
    }

    auto addressHandle = value.As<v8::Object>()->Get(context, StringViewToJS("address", isolate));
    auto timeHandle = value.As<v8::Object>()->Get(context, StringViewToJS("time", isolate));
    auto nameHandle = value.As<v8::Object>()->Get(context, StringViewToJS("name", isolate));
    auto reasonHandle = value.As<v8::Object>()->Get(context, StringViewToJS("reason", isolate));

    if (addressHandle.IsEmpty() || timeHandle.IsEmpty() || nameHandle.IsEmpty() || reasonHandle.IsEmpty()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An object doesn't have required fields").ToLocalChecked()));
        return BanEntry("");
    }

    auto address = JSToStringView(addressHandle.ToLocalChecked(), context);

    L_DEBUG << "address " << address << " " << address.size() << " \"" << address.data() << "\"";

    auto msCount = static_cast<long long>(timeHandle.ToLocalChecked().As<v8::Date>()->ValueOf());
    auto ms = Milliseconds(msCount);
    WorldTimePoint time = WorldTimePoint(ms);

    auto name = JSToStringView(nameHandle.ToLocalChecked(), context);
    auto reason = JSToStringView(reasonHandle.ToLocalChecked(), context);

//    WHY
//    [01/02/2022 - 02:13:14] -> [DEBUG]: address 123 3 "123"
//    [01/02/2022 - 02:13:14] -> [DEBUG]: address be   45 3
//    [01/02/2022 - 02:13:14] -> [DEBUG]: address to js
//        {
//            ban: {
//                address: ' \x003',
//                time: 2022-01-31T23:13:14.089Z,
//                name: ' ',
//                reason: ' '
//            }
//        }


    // todo: consider default and missing parameters

    auto be = BanEntry(address, name, reason, time);

    L_DEBUG << "address be " << be.address.data() << " " << be.address.UsableStaticSize << " " << be.address.length();

    return be;
}

v8::Local<v8::Number> FloatToJS(float value, v8::Isolate *isolate) {
    return v8::Number::New(isolate, value);
}

v8::Local<v8::Integer> IntToJS(int value, v8::Isolate *isolate) {
    return v8::Integer::New(isolate, value);
}

v8::Local<v8::Integer> UIntToJS(unsigned int value, v8::Isolate *isolate) {
    return v8::Integer::NewFromUnsigned(isolate, value);
}

v8::Local<v8::String> StringViewToJS(StringView str, v8::Isolate *isolate) {
    return v8::String::NewFromUtf8(isolate, str.data(), v8::NewStringType::kNormal, str.size()).ToLocalChecked();
}

v8::Local<v8::Boolean> BoolToJS(bool value, v8::Isolate *isolate) {
    return v8::Boolean::New(isolate, value);
}

v8::Local<v8::Object> PlayerKeyDataToJS(PlayerKeyData &data, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    auto dataTemplate = v8::ObjectTemplate::New(context->GetIsolate());

    dataTemplate->Set(v8::String::NewFromUtf8(isolate, "keys").ToLocalChecked(),
                      v8::Integer::NewFromUnsigned(isolate, data.keys));
    dataTemplate->Set(v8::String::NewFromUtf8(isolate, "upDown").ToLocalChecked(),
                      v8::Integer::New(isolate, data.upDown));
    dataTemplate->Set(v8::String::NewFromUtf8(isolate, "leftRight").ToLocalChecked(),
                      v8::Integer::New(isolate, data.leftRight));

    auto object = dataTemplate->NewInstance(context).ToLocalChecked();

    return object;
}

v8::Local<v8::Object> BanEntryToJS(const BanEntry &entry, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    auto dataTemplate = v8::ObjectTemplate::New(context->GetIsolate());

    auto object = dataTemplate->NewInstance(context).ToLocalChecked();

    L_DEBUG << "address to js " << entry.address.data();

    object->Set(context,
                v8::String::NewFromUtf8(isolate, "address").ToLocalChecked(),
                StringViewToJS(entry.address, isolate)).Check();

    auto sinceEpoch = entry.time.time_since_epoch();
    auto ms = std::chrono::duration_cast<Milliseconds>(sinceEpoch);
    auto date = v8::Date::New(context, static_cast<double>(ms.count())).ToLocalChecked();

    object->Set(context, v8::String::NewFromUtf8(isolate, "time").ToLocalChecked(), date).Check();

    object->Set(context,
                v8::String::NewFromUtf8(isolate, "name").ToLocalChecked(),
                StringViewToJS(entry.name, isolate)).Check();
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "reason").ToLocalChecked(),
                StringViewToJS(entry.reason, isolate)).Check();

    // todo: add real checking (error handling)

    return object;
}

HandleStorage *GetContextHandleStorage(const v8::FunctionCallbackInfo<v8::Value> &info) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(info.This()->GetInternalField(0));

    return static_cast<HandleStorage *>( pointer->Value());
}