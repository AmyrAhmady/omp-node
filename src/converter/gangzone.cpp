#include "gangzone.hpp"
#include "primitive.hpp"
#include "types.hpp"
#include "../wrapper/utils.hpp"
#include "entity.hpp"

OBJECT_CONVERTER_DEFINE(GangZonePos,
                        (Vector2, min, VectorToJS<Vector2>, JSToVector<Vector2>),
                        (Vector2, max, VectorToJS<Vector2>, JSToVector<Vector2>))

v8::Local<v8::Array> FlatPtrHashSetIGangZoneToJS(const FlatPtrHashSetIGangZone &gangZones,
                                                 v8::Local<v8::Context> context) {
    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), gangZones.size());

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    int i = 0;
    for (auto gangZone: gangZones) {
        array->Set(context, i++, EntityToJS<IGangZone>(*gangZone, context)).Check();
    }

    return array;
}