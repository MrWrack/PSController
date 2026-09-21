# First retail-17559 test-build checklist

The first build is a **controller startup diagnostic build**, not a claim that
AUX, Party Chat, Game Chat or USB headset audio is finished.

Before loading it on hardware:

- Keep DashLaunch plugin bypass/recovery available.
- Keep the existing working plugins unchanged.
- Use the free plugin slot for `Hdd:\\PSController\\PSController.xex`.
- Confirm the console reports kernel 17559.
- Do not enable HID detours unless verified signatures have been supplied.
- If startup reports a signature mismatch, stop there; do not bypass the guard.

Expected first-run diagnostic sequence:

`controller_starting -> controller_ready -> audio_starting -> ready`

If controller startup fails, inspect both `controller_result` and
`hook_status`. The new `test_build_status::capture()` helper packages these
values with a readable hook message for debug output.

Controller acceptance checks after the native runtime is fully bound:

1. Boot with no PlayStation controller connected.
2. Connect DualSense by USB and verify dashboard input.
3. Disconnect/reconnect it repeatedly and verify no freeze.
4. Repeat with DualShock 4.
5. Connect an unrelated USB device and verify PSController does not claim it.
6. Only after controller stability is established, test AUX insertion/removal.

Audio/voice acceptance comes later. A successful controller diagnostic run
must not be described as working Party Chat/Game Chat/audio support.
