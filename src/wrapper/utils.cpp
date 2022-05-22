#include "utils.hpp"

IHandleStorage *GetHandleStorageExtension(IExtensible *extensible) {
    return queryExtension<IHandleStorage>(extensible);
}

IHandleStorage::IHandleStorage(v8::Isolate *isolate, v8::Local<v8::Value> value)
    : isolate(isolate), storedValue(isolate, value) {
    L_DEBUG << "constructed";
}

v8::Local<v8::Value> IHandleStorage::get() {
    v8::EscapableHandleScope hs(isolate);
    return hs.Escape(storedValue.Get(isolate));
}

void IHandleStorage::freeExtension() {
    isolate = nullptr;
    storedValue.Reset();
    IExtension::freeExtension();
    L_DEBUG << "freed";
}

void IHandleStorage::reset() {
    L_DEBUG << "reset";
}

float JSToFloat(v8::Local<v8::Value> value, v8::Local<v8::Context> context, float defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    return static_cast<float>(value->ToNumber(context).ToLocalChecked()->NumberValue(context).ToChecked());
}

int JSToInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context, int defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    return static_cast<int>(value->ToInteger(context).ToLocalChecked()->Int32Value(context).ToChecked());
}

unsigned int JSToUInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context, int defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    return static_cast<unsigned int>(value->ToInteger(context).ToLocalChecked()->Int32Value(context).ToChecked());
}

Impl::String JSToString(v8::Local<v8::Value> value, v8::Local<v8::Context> context, Impl::String defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    return utils::js_to_string(isolate, value);
}

WorldTimePoint JSToWorldTimePoint(v8::Local<v8::Value> value,
                                  v8::Local<v8::Context> context,
                                  WorldTimePoint defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    auto msCount = static_cast<long long>(value.As<v8::Date>()->ValueOf());
    auto ms = Milliseconds(msCount);

    return WorldTimePoint(ms);
}

bool JSToBool(v8::Local<v8::Value> value, v8::Local<v8::Context> context, bool defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    return value->ToBoolean(isolate)->Value();
}

Vector3 JSToVector3(v8::Local<v8::Value> value, v8::Local<v8::Context> context, Vector3 defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

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

Vector4 JSToVector4(v8::Local<v8::Value> value, v8::Local<v8::Context> context, Vector4 defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    if (!value->IsArray()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An array is required").ToLocalChecked()));
        return Vector4();
    }

    auto xHandle = value.As<v8::Array>()->Get(context, 0);
    auto yHandle = value.As<v8::Array>()->Get(context, 1);
    auto zHandle = value.As<v8::Array>()->Get(context, 2);
    auto wHandle = value.As<v8::Array>()->Get(context, 3);

    if (xHandle.IsEmpty() || yHandle.IsEmpty() || zHandle.IsEmpty() || wHandle.IsEmpty()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An array must contain 4 numbers").ToLocalChecked()));
        return Vector4();
    }

    auto x = JSToFloat(xHandle.ToLocalChecked(), context);
    auto y = JSToFloat(yHandle.ToLocalChecked(), context);
    auto z = JSToFloat(zHandle.ToLocalChecked(), context);
    auto w = JSToFloat(wHandle.ToLocalChecked(), context);

    return {
        x,
        y,
        z,
        w
    };
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
        return {};
    }

    return static_cast<int>(value->ToInteger(context).ToLocalChecked()->Int32Value(context).ToChecked());
}

unsigned int JSToUInt(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return {};
    }

    return static_cast<unsigned int>(value->ToInteger(context).ToLocalChecked()->Int32Value(context).ToChecked());
}

Impl::String JSToString(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return Impl::String();
    }

    return utils::js_to_string(isolate, value);
}

WorldTimePoint JSToWorldTimePoint(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return WorldTimePoint();
    }

    auto msCount = static_cast<long long>(value.As<v8::Date>()->ValueOf());
    auto ms = Milliseconds(msCount);

    return WorldTimePoint(ms);
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

Vector4 JSToVector4(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (!value->IsArray()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An array is required").ToLocalChecked()));
        return Vector4();
    }

    auto xHandle = value.As<v8::Array>()->Get(context, 0);
    auto yHandle = value.As<v8::Array>()->Get(context, 1);
    auto zHandle = value.As<v8::Array>()->Get(context, 2);
    auto wHandle = value.As<v8::Array>()->Get(context, 3);

    if (xHandle.IsEmpty() || yHandle.IsEmpty() || zHandle.IsEmpty() || wHandle.IsEmpty()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An array must contain 3 numbers").ToLocalChecked()));
        return Vector4();
    }

    auto x = JSToFloat(xHandle.ToLocalChecked(), context);
    auto y = JSToFloat(yHandle.ToLocalChecked(), context);
    auto z = JSToFloat(zHandle.ToLocalChecked(), context);
    auto w = JSToFloat(wHandle.ToLocalChecked(), context);

    return {
        x,
        y,
        z,
        w
    };
}

BanEntry JSToBanEntry(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (!value->IsObject()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An object is required").ToLocalChecked()));
        return BanEntry("");
    }

    auto addressHandle = value.As<v8::Object>()->Get(context, StringViewToJS("address", context));
    auto timeHandle = value.As<v8::Object>()->Get(context, StringViewToJS("time", context));
    auto nameHandle = value.As<v8::Object>()->Get(context, StringViewToJS("name", context));
    auto reasonHandle = value.As<v8::Object>()->Get(context, StringViewToJS("reason", context));

    if (addressHandle.IsEmpty() || timeHandle.IsEmpty() || nameHandle.IsEmpty() || reasonHandle.IsEmpty()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An object doesn't have required fields").ToLocalChecked()));
        return BanEntry("");
    }

    auto address = JSToString(addressHandle.ToLocalChecked(), context);
    auto time = JSToWorldTimePoint(timeHandle.ToLocalChecked(), context);
    auto name = JSToString(nameHandle.ToLocalChecked(), context);
    auto reason = JSToString(reasonHandle.ToLocalChecked(), context);

    // todo: consider default and missing parameters

    return BanEntry(address, name, reason, time);
}

IPlayer *JSToIPlayer(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(value.As<v8::Object>()->GetInternalField(0));

    return static_cast<IPlayer *>( pointer->Value());
}

v8::Local<v8::Number> FloatToJS(float value, v8::Local<v8::Context> context) {
    return v8::Number::New(context->GetIsolate(), value);
}

v8::Local<v8::Integer> IntToJS(int value, v8::Local<v8::Context> context) {
    return v8::Integer::New(context->GetIsolate(), value);
}

v8::Local<v8::Integer> UIntToJS(unsigned int value, v8::Local<v8::Context> context) {
    return v8::Integer::NewFromUnsigned(context->GetIsolate(), value);
}

v8::Local<v8::String> StringViewToJS(StringView str, v8::Local<v8::Context> context) {
    return v8::String::NewFromUtf8(context->GetIsolate(),
                                   str.data(),
                                   v8::NewStringType::kNormal,
                                   str.size()).ToLocalChecked();
}

v8::Local<v8::Date> WorldTimePointToJS(WorldTimePoint point, v8::Local<v8::Context> context) {
    auto sinceEpoch = point.time_since_epoch();

    auto ms = duration_cast<Milliseconds>(sinceEpoch);

    v8::Local<v8::Date> date = v8::Date::New(context, static_cast<double>(ms.count())).ToLocalChecked().As<v8::Date>();

    return date;
}

v8::Local<v8::Boolean> BoolToJS(bool value, v8::Local<v8::Context> context) {
    return v8::Boolean::New(context->GetIsolate(), value);
}

v8::Local<v8::Array> Vector3ToJS(Vector3 vector, v8::Local<v8::Context> context) {
    v8::EscapableHandleScope handle_scope(context->GetIsolate());

    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), 3);

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    // Fill out the values
    array->Set(context, 0, v8::Number::New(context->GetIsolate(), vector[0]));
    array->Set(context, 1, v8::Number::New(context->GetIsolate(), vector[1]));
    array->Set(context, 2, v8::Number::New(context->GetIsolate(), vector[2]));

    return handle_scope.Escape(array);
}

v8::Local<v8::Array> Vector4ToJS(Vector4 vector, v8::Local<v8::Context> context) {
    v8::EscapableHandleScope handle_scope(context->GetIsolate());

    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), 4);

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    // Fill out the values
    array->Set(context, 0, v8::Number::New(context->GetIsolate(), vector[0]));
    array->Set(context, 1, v8::Number::New(context->GetIsolate(), vector[1]));
    array->Set(context, 2, v8::Number::New(context->GetIsolate(), vector[2]));
    array->Set(context, 3, v8::Number::New(context->GetIsolate(), vector[3]));

    return handle_scope.Escape(array);
}

v8::Local<v8::Object> SemanticVersionToJS(SemanticVersion &version, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    auto versionObjectTemplate = v8::ObjectTemplate::New(isolate);

    versionObjectTemplate->Set(v8::String::NewFromUtf8(isolate, "major").ToLocalChecked(),
                               v8::Integer::NewFromUnsigned(isolate, version.major));
    versionObjectTemplate->Set(v8::String::NewFromUtf8(isolate, "minor").ToLocalChecked(),
                               v8::Integer::NewFromUnsigned(isolate, version.minor));
    versionObjectTemplate->Set(v8::String::NewFromUtf8(isolate, "patch").ToLocalChecked(),
                               v8::Integer::NewFromUnsigned(isolate, version.patch));
    versionObjectTemplate->Set(v8::String::NewFromUtf8(isolate, "prerel").ToLocalChecked(),
                               v8::Integer::NewFromUnsigned(isolate, version.prerel));

    auto object = versionObjectTemplate->NewInstance(context).ToLocalChecked();

    return object;
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

    object->Set(context,
                v8::String::NewFromUtf8(isolate, "address").ToLocalChecked(),
                StringViewToJS(entry.address, context)).Check();

    object->Set(context,
                v8::String::NewFromUtf8(isolate, "time").ToLocalChecked(),
                WorldTimePointToJS(entry.time, context)).Check();

    object->Set(context,
                v8::String::NewFromUtf8(isolate, "name").ToLocalChecked(),
                StringViewToJS(entry.name, context)).Check();
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "reason").ToLocalChecked(),
                StringViewToJS(entry.reason, context)).Check();

    // todo: add real checking (error handling)

    return object;
}

v8::Local<v8::Object> PlayerBulletDataToJS(const PlayerBulletData &bulletData, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    auto dataTemplate = v8::ObjectTemplate::New(context->GetIsolate());

    auto object = dataTemplate->NewInstance(context).ToLocalChecked();

    object->Set(context,
                v8::String::NewFromUtf8(isolate, "origin").ToLocalChecked(),
                Vector3ToJS(bulletData.origin, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "hitPos").ToLocalChecked(),
                Vector3ToJS(bulletData.hitPos, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "offset").ToLocalChecked(),
                Vector3ToJS(bulletData.offset, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "weapon").ToLocalChecked(),
                UIntToJS(bulletData.weapon, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "hitType").ToLocalChecked(),
                UIntToJS(bulletData.hitType, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "hitID").ToLocalChecked(),
                UIntToJS(bulletData.hitID, context));

    // todo: add real checking (error handling)

    return object;
}