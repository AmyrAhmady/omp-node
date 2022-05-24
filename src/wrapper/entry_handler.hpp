#pragma once

#include "sdk.hpp"
#include "v8.h"

template <class Interface>
using WrapperFunction = void (*)(Interface *, v8::Local<v8::Context>);

template<class Interface>
struct NodeJSEntryHandler : PoolEventHandler<Interface> {
    v8::Isolate *isolate;
    v8::UniquePersistent<v8::Context> context;
    WrapperFunction<Interface> wrap;

    NodeJSEntryHandler(v8::Local<v8::Context> _context, WrapperFunction<Interface> _wrap)
        : isolate(_context->GetIsolate()), context(_context->GetIsolate(), _context), wrap(_wrap) {
    }

    /// Called right after a new entry was constructed
    void onPoolEntryCreated(Interface &entry) override {
        L_DEBUG << "onPoolEntryCreated";
        v8::Locker locker(isolate);
        v8::Isolate::Scope isolateScope(isolate);

        v8::HandleScope scope(isolate);

        auto _context = context.Get(isolate);

        v8::Context::Scope contextScope(_context);

        wrap(&entry, _context);
    };

    /// Called just before an entry is destructed
    void onPoolEntryDestroyed(Interface &entry) override {
        v8::Locker locker(isolate);
        v8::Isolate::Scope isolateScope(isolate);

        v8::HandleScope scope(isolate);

        auto _context = context.Get(isolate);

        v8::Context::Scope contextScope(_context);

        auto handleStorage = GetHandleStorageExtension(&entry);

        if (handleStorage != nullptr) {
            auto entryHandle = handleStorage->get();

            entryHandle.template As<v8::Object>()->SetInternalField(0, v8::External::New(isolate, nullptr));
        }
    };
};