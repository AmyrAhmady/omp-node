#include "../../logger.hpp"
#include "gtaquat_wrapper.hpp"
#include "../../converter/entity.hpp"
#include "../../converter/types.hpp"

FlatHashMap<const GTAQuat*, v8::UniquePersistent<v8::Object>> GTAQuatMap;

void DeleteGTAQuat(const v8::WeakCallbackInfo<GTAQuat>& data) {
    auto quat = data.GetParameter();

    auto existingHandleIterator = GTAQuatMap.find(quat);

    if (existingHandleIterator != GTAQuatMap.end()) {
        GTAQuatMap.erase(existingHandleIterator);

        delete quat;
    }
}

void StoreGTAQuatHandle(v8::Isolate *isolate, v8::Local<v8::Object> handle) {
    v8::Local<v8::External> pointer = v8::Local<v8::External>::Cast(handle->GetInternalField(0));
    auto quat = static_cast<const GTAQuat *>( pointer->Value());

    v8::UniquePersistent<v8::Object> persistent(isolate, handle);

    persistent.SetWeak(const_cast<GTAQuat*>(quat), DeleteGTAQuat, v8::WeakCallbackType::kParameter);

    GTAQuatMap.emplace(quat, std::move(persistent));
}

void GTAQuatConstructor(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    if (!info.IsConstructCall()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "GTAQuat is a constructor").ToLocalChecked()));

        return;
    }

    if (info.Length() == 0) {
        auto quat = new GTAQuat();

        info.This()->SetInternalField(0, v8::External::New(isolate, quat));

        StoreGTAQuatHandle(isolate, info.This());

        info.GetReturnValue().Set(info.This());
    } else if (info.Length() == 4) {
        v8::TryCatch tryCatch(isolate);

        auto w = JSToFloat(info[0], context);
        auto x = JSToFloat(info[1], context);
        auto y = JSToFloat(info[2], context);
        auto z = JSToFloat(info[3], context);

        if (tryCatch.HasCaught()) {
            tryCatch.ReThrow();
            return;
        }

        auto quat = new GTAQuat(w, x, y, z);

        info.This()->SetInternalField(0, v8::External::New(isolate, quat));

        StoreGTAQuatHandle(isolate, info.This());

        info.GetReturnValue().Set(info.This());
    } else if (info.Length() == 3) {
        v8::TryCatch tryCatch(isolate);

        auto x = JSToFloat(info[0], context);
        auto y = JSToFloat(info[1], context);
        auto z = JSToFloat(info[2], context);

        if (tryCatch.HasCaught()) {
            tryCatch.ReThrow();
            return;
        }

        auto quat = new GTAQuat(x, y, z);

        info.This()->SetInternalField(0, v8::External::New(isolate, quat));

        StoreGTAQuatHandle(isolate, info.This());

        info.GetReturnValue().Set(info.This());
    } else if (info.Length() == 1) {
        if (info[0]->IsExternal()) {

            auto srcQuat = static_cast<GTAQuat*>(info[0].As<v8::External>()->Value());

            auto quat = new GTAQuat(*srcQuat);

            info.This()->SetInternalField(0, v8::External::New(isolate, quat));

            StoreGTAQuatHandle(isolate, info.This());

            info.GetReturnValue().Set(info.This());
        } else {
            v8::TryCatch tryCatch(isolate);

            auto vec = JSToVector<Vector3>(info[0], context);

            if (tryCatch.HasCaught()) {
                tryCatch.ReThrow();
                return;
            }

            auto quat = new GTAQuat(vec);

            info.This()->SetInternalField(0, v8::External::New(isolate, quat));

            StoreGTAQuatHandle(isolate, info.This());

            info.GetReturnValue().Set(info.This());
        }
    } else {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Wrong GTAQuat constructor arguments").ToLocalChecked()));
    }
}

WRAP_BASIC_WITH_CONSTRUCTOR_CALLBACK(GTAQuat, GTAQuatConstructor)

WRAP_BASIC_CALL_RETURN(GTAQuat, ToEuler, (Vector3, VectorToJS<Vector3>))

WRAP_ACCESSOR(GTAQuat, w, q.w, (float, FloatToJS), (float, JSToFloat, w))
WRAP_ACCESSOR(GTAQuat, x, q.x, (float, FloatToJS), (float, JSToFloat, x))
WRAP_ACCESSOR(GTAQuat, y, q.y, (float, FloatToJS), (float, JSToFloat, y))
WRAP_ACCESSOR(GTAQuat, z, q.z, (float, FloatToJS), (float, JSToFloat, z))

v8::Local<v8::Object> GTAQuatToJS(const GTAQuat &data, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    v8::EscapableHandleScope hs(isolate);

    auto existingHandleIterator = GTAQuatMap.find(&data);

    if (existingHandleIterator != GTAQuatMap.end()) {
        auto handle = existingHandleIterator->second.Get(isolate);

        return hs.Escape(handle);
    } else {
        auto GTAQuatConstructor = context->Global()->Get(context, v8::String::NewFromUtf8(isolate, "GTAQuat").ToLocalChecked()).ToLocalChecked().As<v8::Function>();

        v8::Local<v8::Value> args[1];
        args[0] = v8::External::New(isolate, const_cast<GTAQuat*>(&data));
        auto handle = GTAQuatConstructor->NewInstance(context, 1, args).ToLocalChecked();

        return hs.Escape(handle);
    }
}

GTAQuat JSToGTAQuat(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    auto GTAQuatConstructor = context->Global()->Get(context, v8::String::NewFromUtf8(isolate, "GTAQuat").ToLocalChecked()).ToLocalChecked().As<v8::Function>();

    if (!value->InstanceOf(context, GTAQuatConstructor).FromJust()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "Parameter is not an instance of GTAQuat").ToLocalChecked()));
        return {};
    }

    auto obj = value.As<v8::Object>();

    v8::Local<v8::External> pointer = v8::Local<v8::External>::Cast(obj->GetInternalField(0));

    auto quat = static_cast<const GTAQuat *>( pointer->Value());

    return *quat;
}