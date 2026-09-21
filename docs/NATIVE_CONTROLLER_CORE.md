# Native controller core safety layer

This is the first source-level piece of the native hiddriver360 callback
adaptation.

It centralizes three rules required before the complete 17559 callback is
enabled:

- Never access a controller slot when lookup returns `-1`.
- Send raw HID input to the PSController observer without consuming it.
- Preserve the report-buffer pointer before the native slot is cleared during
  removal.

The real hiddriver360 callback still owns HID parsing, Xbox button state,
Nintendo-specific handling and USB transfer requeue. This layer is intentionally
small so audio/AUX observation cannot accidentally replace those paths.

The next native merge must map the upstream `Controller` and
`HidControllerExtension` fields into `NativeSlot`, invoke
`observe_interrupt` only after a valid lookup, and invoke `observe_remove`
before cleanup. Hardware testing on retail 17559 remains required.
