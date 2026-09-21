# Retail 17559 platform binding

`retail17559_platform` connects the generic controller startup layer to the
guarded retail-17559 detour layer.

The eventual XEX entry code supplies only the native primitives and real hook
functions: kernel build query, module/export lookup, safe memory read, detour
install/remove, HID add/remove hooks, and XInput/XAM hooks.

Binding does not install hooks by itself. `controller_startup::initialize()`
still performs the exact 17559 check and export resolution first. The guarded
hook installer then verifies HID target prefixes before writing detours.

This keeps unsafe absolute writes out of startup and continues to fail closed.
