# PC smoke test

This is the first test that can run on a normal Windows PC without an Xbox 360
SDK or an RGH console.

Run:

`tools\\run-pc-smoke-test.bat`

The test compiles only portable code and verifies the first-test safety
identity:

- target kernel is 17559,
- mode is diagnostic-only,
- HID hooks are disabled,
- audio is disabled.

A successful PC smoke test does **not** prove that an Xbox 360 XEX will load,
that DualShock/DualSense input works, or that audio/Party Chat works. Those
require the target build environment and physical Xbox 360 testing.

The script expects Microsoft's `cl.exe`. If it is missing, install Visual
Studio Build Tools with the C++ desktop workload and run the script from a
Developer Command Prompt.
