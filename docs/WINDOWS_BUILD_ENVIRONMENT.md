# Windows build environment checklist

PSController's portable source can be prepared before the Xbox 360 compiler is
installed. The final `.xex` build still requires a compatible, legally
obtained Xbox 360 development/build environment.

## PC prerequisites

- Windows PC
- Git
- A C/C++ development environment/editor (Visual Studio is suitable for editing
  and host-side checks)
- The compatible Xbox 360 compiler/linker/XEX tools that will actually be used
  for the target build

Do not commit proprietary SDK headers, libraries, executables, or build tools to
this repository.

## Before enabling a target build

Record these values for the chosen environment:

- compiler executable and version
- C++ language/version support
- linker executable/version
- include paths
- library paths
- XEX generation step
- module-entry convention
- debug output facility

Only after those are known should the toolchain-specific DllMain/shim be added.

## First target build

The first target executable must call the existing
`xex_shim_contract`/native-test-host path and remain diagnostic-only.

Expected behavior:

1. accept kernel 17559,
2. emit startup diagnostics,
3. read 32 bytes from HID_ADD and HID_REMOVE,
4. emit both byte sequences,
5. install no HID detours,
6. start no audio subsystem.

The first build is not a controller-support release. It is a safe hardware
probe used to verify the data required by the later runtime build.
