#include "player.hpp"
#include "primitive.hpp"
#include "types.hpp"
#include "actor.hpp"
#include "../wrapper/utils.hpp"

OBJECT_CONVERTER_DEFINE_TO_JS(ActorSpawnData,
                              (Vector3, position, VectorToJS<Vector3>, JSToVector<Vector3>),
                              (float, facingAngle, FloatToJS, JSToFloat),
                              (int, skin, IntToJS, JSToInt))
                              
IActor *JSToIActor(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(value.As<v8::Object>()->GetInternalField(0));

    return static_cast<IActor *>(pointer->Value());
}

IActor &JSToIActorRef(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast(value.As<v8::Object>()->GetInternalField(0));

    auto pointerValue = static_cast<IActor *>(pointer->Value());

    return *pointerValue;
}

v8::Local<v8::Value> IActorToJS(IActor &actor, v8::Local<v8::Context> context) {
    auto ext = GetHandleStorageExtension(&actor);

    return ext->get();
}
v8::Local<v8::Value> IActorToJS(IActor *actor, v8::Local<v8::Context> context) {
    if (actor == nullptr) {
        return v8::Null(context->GetIsolate());
    }

    auto ext = GetHandleStorageExtension(actor);

    return ext->get();
}