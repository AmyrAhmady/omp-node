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

enum class OmpNodeEventBadRet
{
	None,
	False,
	True
};

enum class OmpNodeEventArgType
{
	Int32,
	UInt32,
	UInt8,
	Ptr,
	Bool,
	Float,
	String
};

struct OmpNodeEventArg
{
	std::variant<int, uint32_t, uint8_t, bool, float, JSString, VoidPtr> value;
	OmpNodeEventArgType type;
};

struct OmpNodeEventArgList
{
	std::size_t size;
	OmpNodeEventArg* data;
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

// Declare omp-node api.
// group - group name, basically a namespace for your api function
// name - name of your api function
// variadic args to basically allow you to declare native variables in C++ to easily use them
#define OMPNODE_API(group, name, ...)                                                                                      \
	class OmpNodeAPI_##group##_##name : public IOmpNodeAPI                                                                 \
	{                                                                                                                      \
	public:                                                                                                                \
		OmpNodeAPI_##group##_##name()                                                                                      \
		{                                                                                                                  \
			OmpNodeAPIManager::Instance().Register(this);                                                                  \
		}                                                                                                                  \
                                                                                                                           \
		void* GetJSAPIHandlerFunction() override                                                                           \
		{                                                                                                                  \
			return reinterpret_cast<void*>(JSAPIHandler);                                                                  \
		}                                                                                                                  \
                                                                                                                           \
		StringView GetName() const override                                                                                \
		{                                                                                                                  \
			return #name;                                                                                                  \
		}                                                                                                                  \
                                                                                                                           \
		StringView GetGroup() const override                                                                               \
		{                                                                                                                  \
			return #group;                                                                                                 \
		}                                                                                                                  \
                                                                                                                           \
		void* GetExternalHandlerFunction() override                                                                        \
		{                                                                                                                  \
			return reinterpret_cast<void*>(NativeHandler);                                                                 \
		}                                                                                                                  \
                                                                                                                           \
	private:                                                                                                               \
		static void JSAPIHandler(void* V8Info)                                                                             \
		{                                                                                                                  \
			auto ompnode = OmpNodeAPIManager::Instance().GetOmpNode();                                                     \
			if (ompnode == nullptr)                                                                                        \
			{                                                                                                              \
				return;                                                                                                    \
			}                                                                                                              \
                                                                                                                           \
			GENERATE_VARIABLES_SAME_AS_ARGS(__VA_ARGS__)                                                                   \
			OmpNodeAPIArg args[] = {                                                                                       \
				GENERATE_OMPNODE_API_ARG_LIST(__VA_ARGS__)                                                                 \
			};                                                                                                             \
                                                                                                                           \
			OmpNodeAPIArgList argList = { OMP_NODE__NUM_ARGS(__VA_ARGS__), args };                                         \
                                                                                                                           \
			ompnode->processV8ArgumentsIntoOmpNodeArgs_UNSAFEINTERNAL(V8Info, argList, [&]() {                             \
				return NativeHandler(GENERATE_PARAMS_TO_USE_IN_FUNCTION_CALL(__VA_ARGS__) true);                           \
			});                                                                                                            \
		}                                                                                                                  \
                                                                                                                           \
		static const nlohmann::json NativeHandler(GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG(__VA_ARGS__) bool dummyArgument); \
                                                                                                                           \
	} OmpNodeAPI_##group##_##name##_instance;                                                                              \
                                                                                                                           \
	const nlohmann::json OmpNodeAPI_##group##_##name::NativeHandler(GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG(__VA_ARGS__) bool dummyArgument)

// Call an event on JS side
// eventName - for event name, as a string
// badRet - the return value that causes your event chain to stop
// pass your arguments after this
#define OMPNODE_CallEvent(eventName, badRet, ...)                                                                                             \
	[]()                                                                                                                                      \
	{                                                                                                                                         \
		Impl::DynamicArray<OmpNodeEventArg> list;                                                                                             \
		int argIndex = 0;                                                                                                                     \
                                                                                                                                              \
		auto callEvent = [&](auto&&... args)                                                                                                  \
		{                                                                                                                                     \
			auto initializer = [&](auto& arg)                                                                                                 \
			{                                                                                                                                 \
				argIndex++;                                                                                                                   \
				using T = std::decay_t<decltype(arg)>;                                                                                        \
				if constexpr (std::is_same_v<T, int>)                                                                                         \
				{                                                                                                                             \
					list.push_back({ arg, OmpNodeEventArgType::Int32 });                                                                      \
				}                                                                                                                             \
				else if constexpr (std::is_same_v<T, uint32_t>)                                                                               \
				{                                                                                                                             \
					list.push_back({ arg, OmpNodeEventArgType::UInt32 });                                                                     \
				}                                                                                                                             \
				else if constexpr (std::is_same_v<T, uint8_t>)                                                                                \
				{                                                                                                                             \
					list.push_back({ arg, OmpNodeEventArgType::UInt8 });                                                                      \
				}                                                                                                                             \
				else if constexpr (std::is_same_v<T, VoidPtr>)                                                                                \
				{                                                                                                                             \
					list.push_back({ arg, OmpNodeEventArgType::Ptr });                                                                        \
				}                                                                                                                             \
				else if constexpr (std::is_same_v<T, bool>)                                                                                   \
				{                                                                                                                             \
					list.push_back({ arg, OmpNodeEventArgType::Bool });                                                                       \
				}                                                                                                                             \
				else if constexpr (std::is_same_v<T, float>)                                                                                  \
				{                                                                                                                             \
					list.push_back({ arg, OmpNodeEventArgType::Float });                                                                      \
				}                                                                                                                             \
				else if constexpr (std::is_same_v<T, Impl::String>)                                                                           \
				{                                                                                                                             \
					list.push_back({ arg, OmpNodeEventArgType::String });                                                                     \
				}                                                                                                                             \
				else if constexpr (std::is_same_v<T, StringView>)                                                                             \
				{                                                                                                                             \
					list.push_back({ arg.to_string(), OmpNodeEventArgType::String });                                                         \
				}                                                                                                                             \
				else if constexpr (std::is_same_v<T, const char*> || std::is_same_v<T, char*>)                                                \
				{                                                                                                                             \
					list.push_back({ Impl::String(arg), OmpNodeEventArgType::String });                                                       \
				}                                                                                                                             \
				else                                                                                                                          \
				{                                                                                                                             \
					throw std::runtime_error(Impl::String("Unable to cast argument ") + std::to_string(argIndex) + "for event " + eventName); \
				}                                                                                                                             \
			};                                                                                                                                \
                                                                                                                                              \
			(initializer(args), ...);                                                                                                         \
		};                                                                                                                                    \
                                                                                                                                              \
		callEvent(__VA_ARGS__);                                                                                                               \
                                                                                                                                              \
		OmpNodeEventArgList args = {                                                                                                          \
			list.size(),                                                                                                                      \
			list.data()                                                                                                                       \
		};                                                                                                                                    \
                                                                                                                                              \
		return OmpNodeAPIManager::Instance().GetOmpNode()->callEvent_UNSAFEINTERNAL(eventName, true, badRet, args);                           \
	}()
