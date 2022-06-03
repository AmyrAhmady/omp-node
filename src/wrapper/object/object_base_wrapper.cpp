#include "object_base_wrapper.hpp"
#include "../../converter/entity.hpp"
#include "../../converter/types.hpp"
#include "../../converter/object.hpp"

WRAP_BASIC_WITH_CONSTRUCTOR_INHERIT(IBaseObject, IEntity)

WRAP_BASIC_CALL(IBaseObject, setDrawDistance, (float, JSToFloat, drawDistance))
WRAP_BASIC_CALL_RETURN(IBaseObject, getDrawDistance, (float, FloatToJS))
WRAP_BASIC_CALL(IBaseObject, setModel, (int, JSToInt, model))
WRAP_BASIC_CALL_RETURN(IBaseObject, getModel, (int, IntToJS<int>))
WRAP_BASIC_CALL(IBaseObject, setCameraCollision, (bool, JSToBool, collision))
WRAP_BASIC_CALL_RETURN(IBaseObject, getCameraCollision, (bool, BoolToJS))
WRAP_BASIC_CALL(IBaseObject, move, (const ObjectMoveData&, FROM_JS_FN(ObjectMoveData), data))
WRAP_BASIC_CALL_RETURN(IBaseObject, isMoving, (bool, BoolToJS))
WRAP_BASIC_CALL(IBaseObject, stop)
WRAP_BASIC_CALL_RETURN(IBaseObject, getMovingData, (const ObjectMoveData&, TO_JS_FN(ObjectMoveData)))
WRAP_BASIC_CALL(IBaseObject,
                attachToVehicle,
                (IVehicle & , JSToEntityRef<IVehicle>, vehicle),
                (Vector3, JSToVector<Vector3>, offset),
                (Vector3, JSToVector<Vector3>, rotation))
WRAP_BASIC_CALL(IBaseObject, resetAttachment)
WRAP_BASIC_CALL_RETURN(IBaseObject, getAttachmentData, (const ObjectAttachmentData&, TO_JS_FN(ObjectAttachmentData)))
WRAP_BASIC_CODE(IBaseObject, getMaterialData, {
    auto external = GetContextExternalPointer<IObject>(info);
    if (external == nullptr) {
        return;
    }
    v8::TryCatch tryCatch(isolate);
    uint32_t materialIndex = JSToUInt<uint32_t>(info[2 - 2], context);
    if (tryCatch.HasCaught()) {
        tryCatch.ReThrow();
        return;
    }
    const ObjectMaterialData *out;
    bool value = external->getMaterialData(materialIndex, out);
    auto valueHandle = BoolToJS(value, context);
    v8::Local<v8::Array> returnArray = v8::Array::New(context->GetIsolate(), 2);
    if (returnArray.IsEmpty())
        return;
    returnArray->Set(context, 0, valueHandle).Check();
    returnArray->Set(context,
                     1,
                     value ? static_cast<v8::Local<v8::Value>>(ObjectMaterialDataToJS(*out, context))
                           : static_cast<v8::Local<v8::Value>>(v8::Null(isolate))).Check();
    info.GetReturnValue().Set(returnArray);
})
WRAP_BASIC_CALL(IBaseObject,
                setMaterial,
                (uint32_t, JSToUInt<uint32_t>, materialIndex),
                (int, JSToInt<int>, model),
                (Impl::String, FROM_JS_FN(String), textureLibrary),
                (Impl::String, FROM_JS_FN(String), textureName),
                (Colour, FROM_JS_FN(Colour), colour))
WRAP_BASIC_CALL(IBaseObject,
                setMaterialText,
                (uint32_t, JSToUInt<uint32_t>, materialIndex),
                (Impl::String, FROM_JS_FN(String), text),
                (ObjectMaterialSize, JSToEnum<ObjectMaterialSize>, materialSize),
                (Impl::String, FROM_JS_FN(String), fontFace),
                (int, JSToInt<int>, fontSize),
                (bool, JSToBool, bold),
                (Colour, FROM_JS_FN(Colour), fontColour),
                (Colour, FROM_JS_FN(Colour), backgroundColour),
                (ObjectMaterialTextAlign, JSToEnum<ObjectMaterialTextAlign>, align))