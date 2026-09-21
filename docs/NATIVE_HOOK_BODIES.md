# Native hook bodies

This layer starts connecting the generic detour/trampoline storage to the
adapted hiddriver360 runtime without guessing the remaining XDK ABI.

## Interrupt path

The real upstream interrupt callback still owns controller parsing, mapping,
state updates and USB requeue. Once it has found a valid slot it may call
`native_hook_bodies::observe_interrupt(driverExtension)`. The observer result
is intentionally discarded, so audio/AUX detection cannot consume controller
input.

## HID removal

`native_hook_bodies::hid_remove` takes a runtime snapshot and checks whether
the device belongs to the adapted hiddriver controller set.

For an owned device it:
1. notifies the AUX/audio observer before cleanup;
2. asks the adapted runtime to perform its normal controller cleanup.

For an unowned device it calls the preserved original HID-remove trampoline.
This keeps ordinary Xbox USB behavior outside PSController's ownership.

The final upstream removal implementation must preserve `reportData` before
zeroing its controller slot and free the saved pointer afterwards.

## Still intentionally missing

The exact native HID-remove ABI must be confirmed in the legal build
environment before this function is installed as a retail hook. The current
`void* -> int` boundary is an integration placeholder based only on the
already-established upstream call shape, not a claim of a verified Xbox kernel
ABI.

No retail-17559 detour is activated by adding these files.
