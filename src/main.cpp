#include <sdk.hpp>

#include "omp-node.hpp"
#include "runtime.hpp"
#include "./api/Impl.hpp"
#include "./api/Pools.hpp"

class OmpNodeComponent final : public IOmpNodeComponent, public CoreEventHandler
{
	StringView componentName() const override
	{
		return "OmpNode";
	}

	SemanticVersion componentVersion() const override
	{
		return SemanticVersion(0, 0, 0, 0);
	}

	void onLoad(ICore* c) override
	{
		core = c;

		omp_initialize_capi(&ompapi);

		runtime = &Runtime::Instance();
		runtime->Init(c, &ompapi);

		c->printLn("OmpNode component loaded");
	}

	void onInit(IComponentList* components) override
	{
		NodeOmpPool::Instance().Init(core, components);
		NodeOmpPool::Instance().AddPoolEvents();
	}

	void provideConfiguration(ILogger& logger, IEarlyConfig& config, bool defaults) override
	{
		if (defaults)
		{
			config.setStrings("node.resources", Span<const StringView>());
			config.setStrings("node.cli_args", Span<const StringView>());

			// inspector
			config.setBool("node.inspector.enable", false);
			config.setInt("node.inspector.port", 9229);
			config.setString("node.inspector.host", "127.0.0.1");
			config.setBool("node.inspector.wait", false);
		}
		else
		{
			if (config.getType("node.resources") == ConfigOptionType_None)
			{
				config.setStrings("node.resources", Span<const StringView>());
			}

			if (config.getType("node.cli_args") == ConfigOptionType_None)
			{
				config.setStrings("node.cli_args", Span<const StringView>());
			}

			if (config.getType("node.inspector.enable") == ConfigOptionType_None)
			{
				config.setBool("node.inspector.enable", false);
			}

			if (config.getType("node.inspector.port") == ConfigOptionType_None)
			{
				config.setInt("node.inspector.port", 9229);
			}

			if (config.getType("node.inspector.host") == ConfigOptionType_None)
			{
				config.setString("node.inspector.host", "127.0.0.1");
			}

			if (config.getType("node.inspector.wait") == ConfigOptionType_None)
			{
				config.setBool("node.inspector.wait", false);
			}
		}
	}

	void onFree(IComponent* component) override
	{
	}

	void onReady() override
	{
		runtime->RunResources();
	}

	void onTick(Microseconds elapsed, TimePoint now) override
	{
		runtime->Tick();
		auto resources = *runtime->GetResources();
		for (auto resource : resources)
		{
			resource->Tick();
		}
	}

	void reset() override
	{
		free();
	}

	void free() override
	{
		delete this;
	}

	void createJSApi_UNSAFEINTERNAL(IOmpNodeAPI* api) override
	{
		APIManager::Instance().Register(api->GetGroup().to_string(), api->GetName().to_string(), reinterpret_cast<APIHandlerFunc_t>(api->GetJSAPIHandlerFunction()));
	}

	void processV8ArgumentsIntoOmpNodeArgs_UNSAFEINTERNAL(void* V8Info, const OmpNodeAPIArgList& retArgList, OmpNodeAPIProcessor handler) override
	{
		const v8::FunctionCallbackInfo<v8::Value>& info = *reinterpret_cast<v8::FunctionCallbackInfo<v8::Value>*>(V8Info);

		v8::Isolate* isolate = info.GetIsolate();
		v8::Local<v8::Context> ctx = isolate->GetEnteredOrMicrotaskContext();

		if (!(info.Length() == retArgList.size))
		{
			helpers::Throw(isolate, (std::to_string(2) + " arguments expected"));
			return;
		};

		for (int i = 0; i < retArgList.size; i++)
		{
			auto arg = retArgList.data[i];
			if (arg.type == OmpNodeAPIArgType::Int32)
			{
				auto value = std::get<int32_t*>(arg.value);
				V8_TO_INT32(info[i + 1], temp);
				*value = temp;
			}
			else if (arg.type == OmpNodeAPIArgType::UInt32)
			{
				auto value = std::get<uint32_t*>(arg.value);
				V8_TO_UINT32(info[i + 1], temp);
				*value = temp;
			}
			else if (arg.type == OmpNodeAPIArgType::UInt8)
			{
				auto value = std::get<uint8_t*>(arg.value);
				V8_TO_UINT8(info[i + 1], temp);
				*value = temp;
			}
			else if (arg.type == OmpNodeAPIArgType::Ptr)
			{
				auto value = std::get<VoidPtr>(arg.value);
				V8_TO_UINTPTR(info[i + 1], temp);
				value = VoidPtr(temp);
			}
			else if (arg.type == OmpNodeAPIArgType::String)
			{
				auto value = std::get<JSString*>(arg.value);
				V8_TO_STRING(info[i + 1], temp);
				*value = temp;
			}
			else if (arg.type == OmpNodeAPIArgType::Bool)
			{
				auto value = std::get<bool*>(arg.value);
				V8_TO_BOOLEAN(info[i + 1], temp);
				*value = temp;
			}
			else if (arg.type == OmpNodeAPIArgType::Float)
			{
				auto value = std::get<float*>(arg.value);
				V8_TO_FLOAT(info[i + 1], temp);
				*value = temp;
			}
			else
			{
				helpers::Throw(isolate, ("Failed to convert value, this type conversion is not handled"));
				return;
			}
		}

		auto result = handler();
		info.GetReturnValue().Set(helpers::JsonToV8(isolate, result));
	}

	bool callEvent_UNSAFEINTERNAL(StringView eventName, bool waitForPromise, OmpNodeEventBadRet badRet, const OmpNodeEventArgList& argList) override
	{
		return Runtime::Instance().DispatchEvents(eventName.to_string(), waitForPromise, badRet, argList);
	}

	~OmpNodeComponent()
	{
		NodeOmpPool::Instance().RemovePoolEvents();
		if (core != nullptr)
		{
			runtime->Dispose();
		}
	}

	ICore* core = nullptr;
	Runtime* runtime = nullptr;
	OMPAPI_t ompapi;
};

COMPONENT_ENTRY_POINT()
{
	return new OmpNodeComponent();
}
