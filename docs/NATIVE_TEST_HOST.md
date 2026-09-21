# Native first-test host boundary

This layer is the final portable boundary before a build-environment-specific
Xbox 360 module entry point.

The native host must supply:

- the detected kernel build,
- the safe memory-read callback,
- debug-line output,
- the existing native service callbacks.

For the first hardware build, `native_test_host::attach()` rejects every
kernel except **17559** and always selects `first_test_entry::safe_default()`.
That means the first build remains diagnostic-only even if other runtime code
exists in the repository.

The intended native entry is conceptually:

```cpp
// Pseudocode only: exact SDK-facing declarations belong in the legal build env.
on_process_attach() {
    native_test_host::Services s = make_native_services();
    return native_test_host::attach(s) == native_test_host::HOST_OK;
}

on_process_detach() {
    native_test_host::detach();
}
```

No Xbox SDK header, library, import ordinal, or ABI is guessed in this portable
file. The final DllMain shim must be written against the actual compatible
toolchain being used to build the XEX.

## First-test invariant

The first XEX must not install HID detours or start audio. Its only runtime
purpose is to prove safe loading on 17559 and collect the two HID target byte
sequences.
