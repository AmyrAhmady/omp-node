#include "utils.hpp"
#include "../converter/primitive.hpp"

IHandleStorage *GetHandleStorageExtension(IExtensible *extensible) {
    return queryExtension<IHandleStorage>(extensible);
}

IHandleStorage::IHandleStorage(v8::Isolate *isolate, v8::Local<v8::Value> value)
    : isolate(isolate), storedValue(isolate, value) {
    L_DEBUG << "IHandleStorage";
}

v8::Local<v8::Value> IHandleStorage::get() {
    v8::EscapableHandleScope hs(isolate);
    return hs.Escape(storedValue.Get(isolate));
}

void IHandleStorage::freeExtension() {
    v8::Locker locker(isolate);
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope scope(isolate);

    auto storedValueHandle = storedValue.Get(isolate);
    storedValueHandle.As<v8::Object>()->SetInternalField(0, v8::External::New(isolate, nullptr));

    storedValue.Reset();
    isolate = nullptr;

    IExtension::freeExtension();
    L_DEBUG << "IHandleStorage::freeExtension";
}

void IHandleStorage::reset() {
    L_DEBUG << "IHandleStorage::reset";
}
