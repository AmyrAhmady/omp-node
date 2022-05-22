#include "utils.hpp"
#include "primitive.hpp"

IHandleStorage *GetHandleStorageExtension(IExtensible *extensible) {
    return queryExtension<IHandleStorage>(extensible);
}

IHandleStorage::IHandleStorage(v8::Isolate *isolate, v8::Local<v8::Value> value)
    : isolate(isolate), storedValue(isolate, value) {
    L_DEBUG << "constructed";
}

v8::Local<v8::Value> IHandleStorage::get() {
    v8::EscapableHandleScope hs(isolate);
    return hs.Escape(storedValue.Get(isolate));
}

void IHandleStorage::freeExtension() {
    isolate = nullptr;
    storedValue.Reset();
    IExtension::freeExtension();
    L_DEBUG << "freed";
}

void IHandleStorage::reset() {
    L_DEBUG << "reset";
}
