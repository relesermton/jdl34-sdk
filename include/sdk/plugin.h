#ifndef JDL34_PLUGIN_H
#define JDL34_PLUGIN_H

#include <sdk.h>

#ifdef __cplusplus
extern "C" {
#endif

#define JDL34_BACKEND_VERSION 1
#define JDL34_PLUGIN_INIT_SYMBOL "jdl34_plugin_init"

struct SdkBackendVtbl {
  uint32_t    version;
  const char* id;
  const char* displayName;

  SdkStatus (*build)(const SdkApi* a, const SdkBuild* b,
                     SdkLogFn log, void* logCtx,
                     char* exeOut, size_t exeOutCap);

  SdkStatus (*probe)(const SdkApi* a, SdkProbeResult* out,
                     char* errBuf, size_t errCap);
};

typedef const SdkBackendVtbl* (*Jdl34PluginInitFn)(const SdkApi* api);

#ifdef __cplusplus
}
#endif

#endif