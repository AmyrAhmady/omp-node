#include "network.hpp"
#include "primitive.hpp"
#include "types.hpp"


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