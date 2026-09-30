#ifndef JDL34_H
#define JDL34_H

#include "sdk.h"
#include "sdk/plugin.h"

#ifdef __cplusplus
extern "C" {
#endif

#define JDL34_VERSION_MAJOR 0
#define JDL34_VERSION_MINOR 1
#define JDL34_VERSION_PATCH 0
#define JDL34_VERSION_STR    "0.1.0"

#define JDL34_SDK_VERSION JDL34_VERSION_STR

#define JDL34_STRINGIFY_IMPL(x) #x
#define JDL34_STRINGIFY(x) JDL34_STRINGIFY_IMPL(x)
#define JDL34_CONCAT_IMPL(a, b) a##b
#define JDL34_CONCAT(a, b) JDL34_CONCAT_IMPL(a, b)

#define JDL34_NARG_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,N,...) N
#define JDL34_NARG1(...) JDL34_NARG_IMPL(__VA_ARGS__,10,9,8,7,6,5,4,3,2,1,0)
#define JDL34_NARG(...) (JDL34_NARG1(__VA_ARGS__))

#define JDL34_ARRAY_LEN(a) (sizeof(a) / sizeof((a)[0]))
#define JDL34_UNUSED(x)    ((void)(x))
#define JDL34_MIN(a, b)    ((a) < (b) ? (a) : (b))
#define JDL34_MAX(a, b)    ((a) > (b) ? (a) : (b))
#define JDL34_CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

#define JDL34_STATIC_ASSERT_IMPL(c, l) typedef char JDL34_CONCAT(jdl34_sa_, l)[(c) ? 1 : -1]
#define JDL34_STATIC_ASSERT(c) JDL34_STATIC_ASSERT_IMPL(c, __LINE__)

#if defined(_MSC_VER)
#  define JDL34_EXPORT __declspec(dllexport)
#  define JDL34_IMPORT __declspec(dllimport)
#  define JDL34_LIKELY(x)   (x)
#  define JDL34_UNLIKELY(x) (x)
#  define JDL34_ASSUME(x)   __assume(x)
#else
#  define JDL34_EXPORT __attribute__((visibility("default")))
#  define JDL34_IMPORT __attribute__((visibility("default")))
#  define JDL34_LIKELY(x)   __builtin_expect(!!(x), 1)
#  define JDL34_UNLIKELY(x) __builtin_expect(!!(x), 0)
#  define JDL34_ASSUME(x)   ((void)0)
#endif

#define JDL34_LOG_DBG(...) jdl34_log_impl(SDK_LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define JDL34_LOG_INF(...) jdl34_log_impl(SDK_LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define JDL34_LOG_WRN(...) jdl34_log_impl(SDK_LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define JDL34_LOG_ERR(...) jdl34_log_impl(SDK_LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)

void jdl34_log_impl(SdkLogLevel level, const char* file, int line, const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif