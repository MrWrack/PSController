# hiddriver360 callback integration

Upstream hiddriver360 queues its interrupt IN transfer in `interruptHandler`,
uses the controller slot's `vendorId` / `productId`, maps the received report,
stores the mapped state, and finally requeues the same interrupt TRB.

PSController now provides a small bridge intended to be called from that exact
path without changing controller mapping:

```cpp
hiddriver_audio_bridge::on_input_report(
    reinterpret_cast<xbox360_usb::DeviceHandle*>(driverExtension->deviceHandle),
    connectedControllers[index].vendorId,
    connectedControllers[index].productId,
    driverExtension->interruptTrb.buffer,
    driverExtension->interruptTrb.length);
```

The integration must happen only after `index >= 0` has been verified. It is
an observer: normal `HidFillButtonsReport`, mapping-assistant handling,
`currentState` assignment, and `UsbdQueueAsyncTransfer` all continue exactly
as before.

Before a matched controller is cleared in `HidRemoveDeviceHook`, call:

```cpp
hiddriver_audio_bridge::on_device_removed(
    reinterpret_cast<xbox360_usb::DeviceHandle*>(deviceHandle2));
```

This clears remembered AUX state only. It does not own or free the controller
handle.

## Important integration fix

The current upstream `interruptHandler` searches for the controller slot and
then accesses `connectedControllers[index]`. PSController integration must
guard `index < 0` before the audio observer is called. Audio code must never
turn a missing slot into a controller crash.

## Build integration

These bridge files are source-side integration points. The full hiddriver360
controller source still has to be imported/merged into PSController under its
GPL-3.0 terms before this call can exist in the final XEX. Do not distribute
proprietary Xbox SDK libraries with the repository.
