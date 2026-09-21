# Native bootstrap

This is the lifecycle wrapper for the eventual Xbox 360 XEX entry point.

Startup:

```text
DllMain/process attach
  -> create xex_native_entry::Services
  -> native_bootstrap::start
       -> xex_native_entry::bind
       -> pscontroller::initialize
       -> guarded controller startup
       -> optional audio startup
```

If controller startup fails, the platform binding is immediately undone.
Optional audio failure must not stop a successfully initialized controller
runtime.

Shutdown performs the reverse order and is safe to call after partial startup.

The final XEX entry unit still needs the legal build environment's actual
module/export lookup, memory-read and detour functions. Those implementations
must not be guessed here, and proprietary SDK libraries/binaries must not be
committed to this repository.

Retail-17559 HID detours also remain blocked until verified target signatures
are supplied.
