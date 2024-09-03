#pragma once

#include <sdk.hpp>
#include <functional>
#include <variant>
#include "./json.hpp"
#include "./macromagic.hpp"

using StringCharPtr = const char*;
using JSString = Impl::String;
using objectPtr = void*;
using VoidPtr = void*;

using OmpNodeAPIProcessor = std::function<nlohmann::json()>;

enum class OmpNodeAPIArgType
{
	Int32,
	UInt32,
	UInt8,
	Ptr,
	Bool,
	Float,
	String
};

struct OmpNodeAPIArg
{
	std::variant<int32_t*, uint32_t*, uint8_t*, bool*, float*, JSString*, VoidPtr> value;
	OmpNodeAPIArgType type;
};

struct OmpNodeAPIArgList
{
	std::size_t size;
	OmpNodeAPIArg* data;
};

class IOmpNodeAPI
{
public:
	/// Get JS API handler function that is used by v8 directly
	virtual void* GetJSAPIHandlerFunction() = 0;

	/// Get JS API name
	virtual StringView GetName() const = 0;

	/// Get JS API group
	virtual StringView GetGroup() const = 0;

	/// Get external handler function used by third party components
	virtual void* GetExternalHandlerFunction() = 0;
};

#define OMPNODE_API(group, name, ...)                                                                                       \
	class OmpNodeAPI_##group##_##name : public IOmpNodeAPI                                                                  \
	{                                                                                                                       \
	public:                                                                                                                 \
		OmpNodeAPI_##group##_##name()                                                                                       \
		{                                                                                                                   \
			OmpNodeAPIManager::Instance().Register(this);                                                                   \
		}                                                                                                                   \
                                                                                                                            \
		void* GetJSAPIHandlerFunction() override                                                                            \
		{                                                                                                                   \
			return reinterpret_cast<void*>(JSAPIHandler);                                                                   \
		}                                                                                                                   \
                                                                                                                            \
		StringView GetName() const override                                                                                 \
		{                                                                                                                   \
			return #name;                                                                                                   \
		}                                                                                                                   \
                                                                                                                            \
		StringView GetGroup() const override                                                                                \
		{                                                                                                                   \
			return #group;                                                                                                  \
		}                                                                                                                   \
                                                                                                                            \
		void* GetExternalHandlerFunction() override                                                                         \
		{                                                                                                                   \
			return reinterpret_cast<void*>(NativeHandler);                                                                  \
		}                                                                                                                   \
                                                                                                                            \
	private:                                                                                                                \
		static void JSAPIHandler(void* V8Info)                                                                              \
		{                                                                                                                   \
			auto ompnode = OmpNodeAPIManager::Instance().GetOmpNode();                                                      \
			if (ompnode == nullptr)                                                                                         \
			{                                                                                                               \
				return;                                                                                                     \
			}                                                                                                               \
                                                                                                                            \
			GENERATE_VARIABLES_SAME_AS_ARGS(__VA_ARGS__)                                                                    \
			OmpNodeAPIArg args[] = {                                                                                        \
				GENERATE_OMPNODE_API_ARG_LIST(__VA_ARGS__)                                                                  \
			};                                                                                                              \
                                                                                                                            \
			OmpNodeAPIArgList argList = { OMP_NODE__NUM_ARGS(__VA_ARGS__), args };                                          \
                                                                                                                            \
			ompnode->processV8ArgumentsIntoOmpNodeArgs_UNSAFEINTERNAL(V8Info, argList, [&]() {                              \
				return NativeHandler(GENERATE_PARAMS_TO_USE_IN_FUNCTION_CALL(__VA_ARGS__) true);                            \
			});                                                                                                             \
		}                                                                                                                   \
                                                                                                                            \
		static const nlohmann::json NativeHandler(GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG(__VA_ARGS__) bool dummyArgument); \
                                                                                                                            \
	} OmpNodeAPI_##group##_##name##_instance;                                                                               \
                                                                                                                            \
	const nlohmann::json OmpNodeAPI_##group##_##name::NativeHandler(GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG(__VA_ARGS__) bool dummyArgument)
