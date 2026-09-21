# Runtime merge step

The imported hiddriver360 parser/mapping source is now paired with a
PSController runtime adapter.

The adapter intentionally does **not** duplicate or replace upstream USB
ownership. The final native `interruptHandler` remains responsible for:

- locating the connected controller slot;
- processing the normal HID/gamepad report;
- updating the Xbox-style controller state;
- requeueing the interrupt transfer.

Once the slot index is known and valid, construct a `ControllerSlot` from the
real hiddriver360 values and call `hiddriver_runtime::observe_interrupt()`.
The observer forwards the unchanged raw report to the DualSense AUX detector.

Before `HidRemoveDeviceHook` clears the matched slot, call
`hiddriver_runtime::observe_remove()`.

This keeps the critical rule: audio failure cannot consume, replace or stop
controller input.

A complete native runtime merge still requires the hiddriver360 main/plugin
entry and its Xbox kernel/XAM hook setup. That code must be adapted rather than
blindly copied because PSController also owns optional audio/voice startup and
shutdown.
