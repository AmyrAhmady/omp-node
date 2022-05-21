#pragma once
#define NODE_WANT_INTERNALS 1
#define USING_UV_SHARED 1

#include "node.h"
#include "env.h"
#include "env-inl.h"
#include "v8.h"
#include "uv.h"
#include "libplatform/libplatform.h"
#include "utils.hpp"
#include "logger.hpp"
#include "sdk.hpp"
#include "wrapper/utils.hpp"

namespace ompnode {
    class Resource {
    public:
        Resource(std::string name, std::string path);
        ~Resource();

        void Init(const std::string &entry = "");
        void Stop();

        inline v8::UniquePersistent<v8::Context> &GetContext() {
            return context;
        }

        node::Environment *GetEnv() {
            return nodeEnvironment.get();
        }

    private:
        v8::UniquePersistent<v8::Context> context;
        std::unique_ptr<node::Environment, decltype(&node::FreeEnvironment)> nodeEnvironment;
        std::string path;
        std::string name;
    };

    namespace v8val {
        inline std::string to_string(v8::Isolate *isolate, const v8::Local<v8::Value> &val) {
            return utils::js_to_string(isolate, val);
        }
        inline const char *to_cstring(v8::Isolate *isolate, const v8::Local<v8::Value> &val) {
            return utils::js_to_cstr(isolate, val);
        }
        void add_definition(const std::string &name, const std::string &value, v8::Local<v8::ObjectTemplate> &global);
    }
}