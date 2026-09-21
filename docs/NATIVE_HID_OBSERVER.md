# Native hiddriver360 observer integration

The native callback bridge is deliberately observational.

In the adapted hiddriver360 interrupt callback:

1. Find the controller slot exactly as upstream does.
2. If the index is negative, do not access the controller array and do not call
   the observer.
3. Build a `NativeControllerView` from the valid slot and interrupt TRB.
4. Call `native_hook_bridge::on_interrupt(view)`.
5. Continue the original mapping, current-state update and async USB requeue
   regardless of the observer result.

For removal, call `native_hook_bridge::on_remove(view)` before the matched
controller slot, report buffer or driver extension is cleared/freed.

The bridge never treats a headset dongle as controller input and never consumes
controller reports. Its purpose is to let the AUX/audio layer observe Sony HID
reports while DS4/DualSense controller behavior remains owned by hiddriver360.

The complete native callback implementation still needs to be adapted from the
GPL upstream source and compiled with the legal Xbox 360 build environment.
