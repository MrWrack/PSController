# XEX native entry boundary

This boundary is the final portable layer before the real Xbox 360 XEX entry
unit.

The build environment must provide:

- kernel build query
- module lookup
- export lookup
- guarded memory read
- detour install/remove implementation
- the five real native hook functions

Those services are passed through `xex_native_entry::bind()` into
`retail17559_platform`, which then supplies `controller_startup`.

The intended startup order is:

1. Construct `xex_native_entry::Services` from the legal Xbox 360 build
   environment.
2. Call `xex_native_entry::bind(services)`.
3. Only if binding succeeds, call `pscontroller::initialize()`.
4. `controller_startup` checks for kernel 17559 and resolves required exports.
5. The guarded hook layer verifies its targets before any detour installation.
6. Optional audio starts only after controller startup succeeds.

Shutdown order:

1. `pscontroller::shutdown()`
2. `xex_native_entry::unbind()`

No proprietary XDK files are included here. No raw absolute kernel write is
performed by this boundary.

## Remaining blocker before a hardware test XEX

The current HID add/remove target signatures in `retail17559_hooks.cpp` still
need independent verification for retail kernel 17559. Until that is done, the
real XEX entry should not activate the detours. The actual native hook bodies
also need their upstream hiddriver360 state machine merged with the observer
patch points documented in `INTERRUPT_HANDLER_MERGE.md`.
