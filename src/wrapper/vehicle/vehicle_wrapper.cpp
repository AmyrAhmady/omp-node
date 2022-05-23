#include "vehicle_wrapper.hpp"
#include "../../logger.hpp"
#include "../../converter/primitive.hpp"

IVehicle *GetVehicleFromContext(const v8::FunctionCallbackInfo<v8::Value> &info) {
    auto vehicle = GetContextExternalPointer<IVehicle>(info);

    if (vehicle == nullptr) {
        info.GetIsolate()->ThrowException(v8::Exception::ReferenceError(v8::String::NewFromUtf8(info.GetIsolate(),
                                                                                                "The vehicle doesn't exist").ToLocalChecked()));
    }

    return vehicle;
}

void setColour(const v8::FunctionCallbackInfo<v8::Value> &info) {
    ENTER_FUNCTION_CALLBACK(info)

    auto vehicle = GetVehicleFromContext(info);

    if (!vehicle)
        return;

    auto col1 = JSToInt(info[0], context);
    auto col2 = JSToInt(info[1], context);

    vehicle->setColour(col1, col2);
}

void WrapVehicle(IVehicle *vehicle, v8::Local<v8::Context> context) {
    ObjectMethods methods = {{"setColour",       setColour}};

    auto vehicleHandle = InterfaceToObject(vehicle, context, methods);

    vehicle->addExtension(new IHandleStorage(context->GetIsolate(), vehicleHandle), true);
}