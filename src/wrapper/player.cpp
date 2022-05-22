#include "player.hpp"
#include "primitive.hpp"

IPlayer *JSToIPlayer(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(value.As<v8::Object>()->GetInternalField(0));

    return static_cast<IPlayer *>( pointer->Value());
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