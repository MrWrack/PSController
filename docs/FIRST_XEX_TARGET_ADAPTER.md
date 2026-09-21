# First XEX target adapter

This adapter is the portable side of the first real Xbox 360 diagnostic XEX.

It deliberately does not include Xbox SDK headers and does not guess a DllMain
ABI. The selected target toolchain must provide three verified services:

1. detect the running kernel build,
2. safely read target memory,
3. write a diagnostic log line.

The adapter rejects any kernel other than 17559. On 17559 it performs only the
existing read-only HID probe and prints HID_ADD/HID_REMOVE bytes. It installs
no controller hooks and starts no audio/voice path.

The remaining target-specific file is intentionally deferred until the actual
compatible Xbox 360 build environment is identified, so its entry-point ABI
and platform calls can be implemented from known definitions rather than
guesses.
