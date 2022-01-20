#ifndef SRC_DEBUG_UTILS_H_
#define SRC_DEBUG_UTILS_H_

#if defined(NODE_WANT_INTERNALS) && NODE_WANT_INTERNALS

#include "async_wrap.h"

#include <algorithm>
#include <sstream>
#include <string>

// Use FORCE_INLINE on functions that have a debug-category-enabled check first
// and then ideally only a single function call following it, to maintain
// performance for the common case (no debugging used).
#ifdef __GNUC__
#define FORCE_INLINE __attribute__((always_inline))
#define COLD_NOINLINE __attribute__((cold, noinline))
#else
#define FORCE_INLINE
#define COLD_NOINLINE
#endif

namespace node {
class Environment;

template <typename T>
inline std::string ToString(const T& value);

// C++-style variant of sprintf()/fprintf() that:
// - Returns an std::string
// - Handles \0 bytes correctly
// - Supports %p and %s. %d, %i and %u are aliases for %s.
// - Accepts any class that has a ToString() method for stringification.
template <typename... Args>
inline std::string SPrintF(const char* format, Args&&... args);
template <typename... Args>
inline void FPrintF(FILE* file, const char* format, Args&&... args);
void FWrite(FILE* file, const std::string& str);

// Listing the AsyncWrap provider types first enables us to cast directly
// from a provider type to a debug category.
#define DEBUG_CATEGORY_NAMES(V)                                                \
  NODE_ASYNC_PROVIDER_TYPES(V)                                                 \
  V(DIAGNOSTICS)                                                               \
  V(HUGEPAGES)                                                                 \
  V(INSPECTOR_SERVER)                                                          \
  V(INSPECTOR_PROFILER)                                                        \
  V(CODE_CACHE)                                                                \
  V(NGTCP2_DEBUG)                                                              \
  V(WASI)                                                                      \
  V(MKSNAPSHOT)

enum class DebugCategory {
#define V(name) name,
  DEBUG_CATEGORY_NAMES(V)
#undef V
      CATEGORY_COUNT
};

class EnabledDebugList {
 public:
  bool enabled(DebugCategory category) const {
    DCHECK_GE(static_cast<int>(category), 0);
    DCHECK_LT(static_cast<int>(category),
              static_cast<int>(DebugCategory::CATEGORY_COUNT));
    return enabled_[static_cast<int>(category)];
  }

  // Uses NODE_DEBUG_NATIVE to initialize the categories. When env is not a
  // nullptr, the environment variables set in the Environment are used.
  // Otherwise the system environment variables are used.
  void Parse(Environment* env);

 private:
  // Set all categories matching cats to the value of enabled.
  void Parse(const std::string& cats, bool enabled);
  void set_enabled(DebugCategory category, bool enabled) {
    DCHECK_GE(static_cast<int>(category), 0);
    DCHECK_LT(static_cast<int>(category),
              static_cast<int>(DebugCategory::CATEGORY_COUNT));
    enabled_[static_cast<int>(category)] = true;
  }

  bool enabled_[static_cast<int>(DebugCategory::CATEGORY_COUNT)] = {false};
};

template <typename... Args>
inline void FORCE_INLINE Debug(EnabledDebugList* list,
                               DebugCategory cat,
                               const char* format,
                               Args&&... args);

inline void FORCE_INLINE Debug(EnabledDebugList* list,
                               DebugCategory cat,
                               const char* message);

template <typename... Args>
inline void FORCE_INLINE
Debug(Environment* env, DebugCategory cat, const char* format, Args&&... args);

inline void FORCE_INLINE Debug(Environment* env,
                               DebugCategory cat,
                               const char* message);

template <typename... Args>
inline void Debug(Environment* env,
                  DebugCategory cat,
                  const std::string& format,
                  Args&&... args);

// Used internally by the 'real' Debug(AsyncWrap*, ...) functions below, so that
// the FORCE_INLINE flag on them doesn't apply to the contents of this function
// as well.
// We apply COLD_NOINLINE to tell the compiler that it's not worth optimizing
// this function for speed and it should rather focus on keeping it out of
// hot code paths. In particular, we want to keep the string concatenating code
// out of the function containing the original `Debug()` call.
template <typename... Args>
void COLD_NOINLINE UnconditionalAsyncWrapDebug(AsyncWrap* async_wrap,
                                               const char* format,
                                               Args&&... args);

template <typename... Args>
inline void FORCE_INLINE Debug(AsyncWrap* async_wrap,
                               const char* format,
                               Args&&... args);

template <typename... Args>
inline void FORCE_INLINE Debug(AsyncWrap* async_wrap,
                               const std::string& format,
                               Args&&... args);

// Debug helper for inspecting the currently running `node` executable.
class NativeSymbolDebuggingContext {
 public:
  static std::unique_ptr<NativeSymbolDebuggingContext> New();

  class SymbolInfo {
   public:
    std::string name;
    std::string filename;
    size_t line = 0;
    size_t dis = 0;

    std::string Display() const;
  };

  NativeSymbolDebuggingContext() = default;
  virtual ~NativeSymbolDebuggingContext() = default;

  virtual SymbolInfo LookupSymbol(void* address) { return {}; }
  virtual bool IsMapped(void* address) { return false; }
  virtual int GetStackTrace(void** frames, int count) { return 0; }

  NativeSymbolDebuggingContext(const NativeSymbolDebuggingContext&) = delete;
  NativeSymbolDebuggingContext(NativeSymbolDebuggingContext&&) = delete;
  NativeSymbolDebuggingContext operator=(NativeSymbolDebuggingContext&)
    = delete;
  NativeSymbolDebuggingContext operator=(NativeSymbolDebuggingContext&&)
    = delete;
  static std::vector<std::string> GetLoadedLibraries();
};

// Variant of `uv_loop_close` that tries to be as helpful as possible
// about giving information on currently existing handles, if there are any,
// but still aborts the process.
void CheckedUvLoopClose(uv_loop_t* loop);
void PrintLibuvHandleInformation(uv_loop_t* loop, FILE* stream);

namespace per_process {
extern EnabledDebugList enabled_debug_list;

template <typename... Args>
inline void FORCE_INLINE Debug(DebugCategory cat,
                               const char* format,
                               Args&&... args);

inline void FORCE_INLINE Debug(DebugCategory cat, const char* message);
}  // namespace per_process
}  // namespace node

#endif  // defined(NODE_WANT_INTERNALS) && NODE_WANT_INTERNALS

#endif  // SRC_DEBUG_UTILS_H_
