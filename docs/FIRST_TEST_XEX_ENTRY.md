# First test XEX entry

The portable first-test entry is now complete.

`first_test_entry::safe_default()` selects:

- diagnostic-only mode,
- 32-byte HID target capture,
- no controller detours,
- no audio startup.

A build-environment-specific Xbox 360 `DllMain` only needs to provide the
native callbacks and invoke `first_test_entry::start()`.

This deliberately keeps the first executable useful even before verified
retail-17559 signatures are available. The first hardware result we need is the
two read-only HID target lines.

After those bytes and the hook ABI are verified, a later build can explicitly
select `MODE_CONTROLLER_RUNTIME`. The default must remain diagnostic-only so a
source/build configuration mistake cannot silently activate experimental
kernel detours.

## What still requires the Xbox build environment

The repository cannot truthfully emit a tested XEX until a compatible legal
Xbox 360 toolchain supplies the platform-specific entry point/imports. No
proprietary SDK files are stored here.

## First hardware success criterion

The console loads the diagnostic plugin, emits both 32-byte HID target lines,
installs no hooks, and returns/stays stable. That result is evidence for the
next controller-runtime build; it is not evidence that controller or audio
support is already working.
