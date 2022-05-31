#pragma once

#include "sdk.hpp"
#include "v8.h"

template<class Interface> using WrapperFunction = void (*)(Interface *, v8::Local<v8::Context>);

static const UID NodeJSEntryHandler_UID = UID(0xbc870166fb590549);

template<class Interface, UID uid = NodeJSEntryHandler_UID>
struct NodeJSEntryHandler : PoolEventHandler<Interface>, public IExtension {
    PROVIDE_EXT_UID(uid);

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

    void freeExtension() override {
        context.Reset();
        isolate = nullptr;

        IExtension::freeExtension();
    }

    void reset() override {
    }
};