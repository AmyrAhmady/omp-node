#include "player.hpp"
#include "primitive.hpp"

//float delta, bool loop, bool lockX, bool lockY, bool freeze, uint32_t time, StringView lib, StringView name

AnimationData JSToAnimationData(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (!value->IsObject()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An object is required").ToLocalChecked()));
        return {};
    }

    auto deltaHandle = value.As<v8::Object>()->Get(context, StringViewToJS("delta", context));
    auto loopHandle = value.As<v8::Object>()->Get(context, StringViewToJS("loop", context));
    auto lockXHandle = value.As<v8::Object>()->Get(context, StringViewToJS("lockX", context));
    auto lockYHandle = value.As<v8::Object>()->Get(context, StringViewToJS("lockY", context));
    auto freezeHandle = value.As<v8::Object>()->Get(context, StringViewToJS("freeze", context));
    auto timeHandle = value.As<v8::Object>()->Get(context, StringViewToJS("time", context));
    auto libHandle = value.As<v8::Object>()->Get(context, StringViewToJS("lib", context));
    auto nameHandle = value.As<v8::Object>()->Get(context, StringViewToJS("name", context));

    if (deltaHandle.IsEmpty() || loopHandle.IsEmpty() || lockXHandle.IsEmpty() || lockYHandle.IsEmpty()
        || freezeHandle.IsEmpty() || timeHandle.IsEmpty() || libHandle.IsEmpty() || nameHandle.IsEmpty()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An object doesn't have required fields").ToLocalChecked()));
        return {};
    }

    auto delta = JSToFloat(deltaHandle.ToLocalChecked(), context);
    auto loop = JSToBool(loopHandle.ToLocalChecked(), context);
    auto lockX = JSToBool(lockXHandle.ToLocalChecked(), context);
    auto lockY = JSToBool(lockYHandle.ToLocalChecked(), context);
    auto freeze = JSToBool(freezeHandle.ToLocalChecked(), context);
    auto time = (uint32_t)JSToUInt(timeHandle.ToLocalChecked(), context);
    auto lib = JSToString(libHandle.ToLocalChecked(), context);
    auto name = JSToString(nameHandle.ToLocalChecked(), context);

    // todo: consider default and missing parameters

    return {
        delta,
        loop,
        lockX,
        lockY,
        freeze,
        time,
        lib,
        name
    };
}

v8::Local<v8::Object> AnimationDataToJS(const AnimationData &animationData,
                                        v8::Local<v8::Context> context) { // todo: provide helper methods of the class to js somehow
    auto isolate = context->GetIsolate();

    auto dataTemplate = v8::ObjectTemplate::New(context->GetIsolate());

    auto object = dataTemplate->NewInstance(context).ToLocalChecked();

    object->Set(context,
                v8::String::NewFromUtf8(isolate, "delta").ToLocalChecked(),
                FloatToJS(animationData.delta, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "loop").ToLocalChecked(),
                BoolToJS(animationData.loop, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "lockX").ToLocalChecked(),
                BoolToJS(animationData.lockX, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "lockY").ToLocalChecked(),
                BoolToJS(animationData.lockY, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "freeze").ToLocalChecked(),
                BoolToJS(animationData.freeze, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "time").ToLocalChecked(),
                UIntToJS(animationData.time, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "lib").ToLocalChecked(),
                StringViewToJS(animationData.lib, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "name").ToLocalChecked(),
                StringViewToJS(animationData.name, context));

    // todo: add real checking (error handling)

    return object;
}

v8::Local<v8::Object> PlayerAnimationDataToJS(const PlayerAnimationData &playerAnimationData,
                                              v8::Local<v8::Context> context) { // todo: provide helper methods of the class to js somehow
    auto isolate = context->GetIsolate();

    auto dataTemplate = v8::ObjectTemplate::New(context->GetIsolate());

    auto object = dataTemplate->NewInstance(context).ToLocalChecked();

    object->Set(context,
                v8::String::NewFromUtf8(isolate, "ID").ToLocalChecked(),
                UIntToJS(playerAnimationData.ID, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "flags").ToLocalChecked(),
                UIntToJS(playerAnimationData.flags, context));

    auto name = playerAnimationData.name();

    object->Set(context, v8::String::NewFromUtf8(isolate, "lib").ToLocalChecked(), StringViewToJS(name.first, context));
    object->Set(context,
                v8::String::NewFromUtf8(isolate, "name").ToLocalChecked(),
                StringViewToJS(name.second, context));

    // todo: add real checking (error handling)

    return object;
}
