# jdl34-sdk

An SDK that compiles **C**, **C++**, **Java**, and **C#** source into Windows `.exe`
files, plus an orchestrating core with a plug-in seam for a future custom compiler backend.

## Layout

```
bin/      command shims (jdl34, jdl34-c, jdl34-cpp, jdl34-java, jdl34-cs, ...)
          plus jdl34-env.bat to put the toolset on your PATH
exec/     runtime: jdl34.exe, per-language launchers, jdl34-cc.exe (built-in
          compiler), nbuild2.exe, jdl34-sdk.dll, backend plug-in DLLs
include/  public C-ABI headers (sdk.h, plugin.h, jdl34.h macro utilities)
  cc/           C include shim added by the c backend (stdio.h, ...)
  c++/lib       C++ include search path added by the c backend (jdl34/core.hpp)
  java/lib/modules  javac module path (-p) added by the java backend
  c#/lib/modules    C# reference-assembly dir added by the cs backend
lib/      import libraries (libjdl34-sdk.dll.a, backend .dll.a) for linking
          against the SDK from your own programs
share/
  samples/      hello-world per language
  doc/          README
misc/
  tests/        end-to-end script (tests\e2e.ps1)
```

## Build (from source)

Requires CMake, Ninja (optional), and gcc (MinGW-w64) or MSVC. The whole toolset
lands in `bin/` at the project root.

```
cmake -G Ninja -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

The prebuilt package ships the same toolset split across `bin/` (shims) and
`exec/` (runtime), so only `bin\` needs to be on your PATH.

## Usage

```
bin\jdl34 probe
bin\jdl34 build --lang c     -o hello share\samples\c\hello.c
bin\jdl34-cpp -o hello share\samples\cpp\hello.cpp      (launcher = build --lang cpp)
bin\jdl34-java --main Hello -o hello share\samples\java\Hello.java
bin\jdl34-cs  -o hello share\samples\cs\Program.cs
hello.exe
```

Run `bin\jdl34-env.bat` first to put both `bin\` and `exec\` on your PATH, or
invoke the shims in `bin\` directly (they forward to `exec\`).

Options: `-I <dir>` / `--inc <dir>`, `-D <def>`, `-O 0-3`, `-g` (debug info),
`--main <class>` (Java main class), `--workdir <dir>`.

## Incremental build driver

`bin\jdl34 driver --lang c -o app.exe src\main.c src\util.c` is a make-style
driver: it fingerprints the sources and flags, skips the compiler when nothing
changed (`up to date`), and rebuilds otherwise. `--force` bypasses the cache.

```
bin\jdl34 driver --lang cpp -O2 -o tools\build\app share\samples\cpp\hello.cpp
```

## Toolchain detection

`bin\jdl34 probe` reports what each backend can use:

- **C/C++** -> gcc/g++ (MinGW-w64) or clang
- **Java** -> javac; real .exe via JDK `jpackage` app-image (or GraalVM `native-image`)
- **C#** -> .NET SDK (`dotnet publish`, self-contained single-file exe)

Missing toolchains produce install guidance (winget) instead of failing silently.

## Cross-language bindings

- **C#** `bindings/csharp/Sdk.cs` — P/Invoke wrapper over `jdl34-sdk.dll`
- **Java** `bindings/java/org/jdl34/Sdk.java` + JNI shim (built when a JDK is present)

## Plugin seam (custom compiler)

Backends are DLLs loaded by the core. Each exports `jdl34_plugin_init` returning a
`SdkBackendVtbl`. To add your own compiler later, implement that vtable; the core
handles probing, process execution, diagnostics, and PE/COFF output plumbing.