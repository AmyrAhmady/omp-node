#include "types.hpp"
#include "primitive.hpp"


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

Milliseconds JSToMilliseconds(v8::Local<v8::Value> value,
                                  v8::Local<v8::Context> context,
                              Milliseconds defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    auto msCount = JSToInt(value, context);
    return Milliseconds(msCount);
}

Vector2 JSToVector2(v8::Local<v8::Value> value, v8::Local<v8::Context> context, Vector2 defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    if (!value->IsArray()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An array is required").ToLocalChecked()));
        return Vector2();
    }

    auto xHandle = value.As<v8::Array>()->Get(context, 0);
    auto yHandle = value.As<v8::Array>()->Get(context, 1);

    if (xHandle.IsEmpty() || yHandle.IsEmpty()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An array must contain 2 numbers").ToLocalChecked()));
        return Vector2();
    }

    auto x = JSToFloat(xHandle.ToLocalChecked(), context);
    auto y = JSToFloat(yHandle.ToLocalChecked(), context);

    return {
        x,
        y
    };
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

Milliseconds JSToMilliseconds(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return Milliseconds();
    }

    auto msCount = JSToInt(value, context);
    return Milliseconds(msCount);
}

Vector2 JSToVector2(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (!value->IsArray()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An array is required").ToLocalChecked()));
        return Vector2();
    }

    auto xHandle = value.As<v8::Array>()->Get(context, 0);
    auto yHandle = value.As<v8::Array>()->Get(context, 1);

    if (xHandle.IsEmpty() || yHandle.IsEmpty()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An array must contain 2 numbers").ToLocalChecked()));
        return Vector2();
    }

    auto x = JSToFloat(xHandle.ToLocalChecked(), context);
    auto y = JSToFloat(yHandle.ToLocalChecked(), context);

    return {
        x,
        y
    };
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


v8::Local<v8::Date> WorldTimePointToJS(WorldTimePoint point, v8::Local<v8::Context> context) {
    auto sinceEpoch = point.time_since_epoch();

    auto ms = duration_cast<Milliseconds>(sinceEpoch);

    v8::Local<v8::Date> date = v8::Date::New(context, static_cast<double>(ms.count())).ToLocalChecked().As<v8::Date>();

    return date;
}

v8::Local<v8::Integer> MillisecondsToJS(Milliseconds ms, v8::Local<v8::Context> context) {
    return IntToJS(ms.count(), context);
}

v8::Local<v8::Array> Vector2ToJS(Vector2 vector, v8::Local<v8::Context> context) {
    v8::EscapableHandleScope handle_scope(context->GetIsolate());

    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), 2);

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    // Fill out the values
    array->Set(context, 0, v8::Number::New(context->GetIsolate(), vector[0]));
    array->Set(context, 1, v8::Number::New(context->GetIsolate(), vector[1]));

    return handle_scope.Escape(array);
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