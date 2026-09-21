# Diagnostic boot mode

This is the bridge between the read-only 17559 target probe and a future native
XEX logger.

A diagnostic build can provide two callbacks:

1. safe kernel-memory read,
2. debug-line output.

Then call:

`diagnostic_boot::run(api, 16)`

or 32 bytes when the logger has enough room.

On success the logger receives one line for `HID_ADD` and one for
`HID_REMOVE`. No detours are installed by this path and no target memory is
written.

This mode is intended to run **before** the normal controller hook startup on
the first hardware test. If the read fails, the diagnostic result reports
`RESULT_CAPTURE_FAILED`; do not fall through into unverified hooks.

The native build-specific logger remains intentionally outside the portable
source because its ABI depends on the legal Xbox 360 build environment.
