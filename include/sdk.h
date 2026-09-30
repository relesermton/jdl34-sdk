#ifndef JDL34_SDK_H
#define JDL34_SDK_H

#include <stdint.h>
#include <stddef.h>
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32)
#  if defined(JDL34_SDK_BUILDING_DLL)
#    define SDK_API __declspec(dllexport)
#  else
#    define SDK_API __declspec(dllimport)
#  endif
#else
#  define SDK_API __attribute__((visibility("default")))
#endif

typedef enum SdkStatus {
  SDK_OK              = 0,
  SDK_ERR_INVALID_ARG = -1,
  SDK_ERR_NOT_FOUND   = -2,
  SDK_ERR_TOOLCHAIN   = -3,
  SDK_ERR_COMPILE     = -4,
  SDK_ERR_IO          = -5,
  SDK_ERR_NOMEM       = -6,
  SDK_ERR_UNSUPPORTED = -7,
  SDK_ERR_INSTALL     = -8,
  SDK_ERR_PLUGIN      = -9,
  SDK_ERR_INTERNAL    = -10
} SdkStatus;

typedef enum SdkLogLevel {
  SDK_LOG_DEBUG = 0,
  SDK_LOG_INFO  = 1,
  SDK_LOG_WARN  = 2,
  SDK_LOG_ERROR = 3
} SdkLogLevel;

typedef void (*SdkLogFn)(void* ctx, SdkLogLevel level, const char* message);

typedef struct SdkBuild {
  const char*  language;
  const char** sources;
  uint32_t     sourceCount;
  const char** includeDirs;
  uint32_t     includeDirCount;
  const char** defines;
  uint32_t     defineCount;
  const char*  outputBase;
  const char*  workDir;
  const char*  mainClass;
  uint32_t     optLevel;
  int          debug;
} SdkBuild;

typedef struct SdkToolchainInfo {
  int  present;
  char name[64];
  char version[64];
  char path[512];
} SdkToolchainInfo;

typedef struct SdkProbeResult {
  SdkToolchainInfo gcc;
  SdkToolchainInfo gpp;
  SdkToolchainInfo clang;
  SdkToolchainInfo javac;
  SdkToolchainInfo nativeImage;
  SdkToolchainInfo dotnet;
} SdkProbeResult;

typedef struct SdkBackendVtbl SdkBackendVtbl;
typedef struct SdkApi        SdkApi;

struct SdkApi {
  const char* (*version)(const SdkApi* a);

  SdkStatus (*probe)(const SdkApi* a, SdkProbeResult* out);

  SdkStatus (*build)(const SdkApi* a, const SdkBuild* b,
                     SdkLogFn log, void* logCtx,
                     char* exeOut, size_t exeOutCap);

  SdkStatus (*register_backend)(const SdkApi* a, const SdkBackendVtbl* vtbl);

  const char* (*error_string)(SdkStatus s);

  void  (*log)(const SdkApi* a, SdkLogLevel lvl, const char* msg);

  int   (*path_exists)(const SdkApi* a, const char* utf8Path);

  void  (*set_last_error)(const SdkApi* a, const char* msg);
  const char* (*last_error)(const SdkApi* a);

  SdkStatus (*run)(const SdkApi* a, const wchar_t* program,
                   const wchar_t* args, int timeoutMs,
                   char** outBuf, size_t* outLen, int* exitCode,
                   char* errBuf, size_t errCap);

  void  (*free)(const SdkApi* a, void* p);

  SdkStatus (*make_temp_dir)(const SdkApi* a, wchar_t* path, size_t capacity);

  int   (*copy_file)(const SdkApi* a, const char* srcUtf8, const char* dstUtf8);

  void  (*utf8_to_wide)(const SdkApi* a, const char* in, wchar_t* out, size_t cap);

  void  (*wide_to_utf8)(const SdkApi* a, const wchar_t* in, char* out, size_t cap);

  size_t (*quote_arg)(const SdkApi* a, const wchar_t* arg, wchar_t* out, size_t cap);

  void  (*module_dir)(const SdkApi* a, wchar_t* out, size_t cap);

  int   (*resource_dir)(const SdkApi* a, wchar_t* out, size_t cap);
};

SDK_API const SdkApi* jdl34_sdk_api(void);

#ifdef __cplusplus
}
#endif

#endif