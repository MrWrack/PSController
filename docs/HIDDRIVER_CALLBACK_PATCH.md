# hiddriver360 callback patch points

Upstream `hiddriver/main.cpp` was checked before defining these patch points.

## Interrupt callback

Upstream searches `connectedControllers` for the matching
`controllerDriver`, but then dereferences `connectedControllers[index]`
without first rejecting `index == -1`.

PSController's adapted callback must add:

```cpp
if (index < 0)
    return 0;
```

immediately after that search and before Nintendo handling or any other
`connectedControllers[index]` access.

After the guard, construct an `InterruptContext` using:

- `driverExtension->deviceHandle`
- `driverExtension`
- `connectedControllers[index].vendorId`
- `connectedControllers[index].productId`
- `driverExtension->interruptTrb.buffer`
- `driverExtension->interruptTrb.length`

and call `native_callback_adapter::observe_valid_interrupt(context)`.

The observer result must not change upstream input behavior. Continue normal
Nintendo handling, HID parsing/mapping, `currentState` update and
`UsbdQueueAsyncTransfer`.

## Removal callback

Upstream `HidRemoveDeviceHook` finds the matching slot and then starts
cleanup. Call `native_callback_adapter::observe_before_remove(context)` after
the slot is found but before `cleanupDone`, report-info cleanup, memset,
driver deletion or report-buffer free.

This ordering preserves the handle and gives the AUX/audio state machine a
reliable disconnect notification.

## Important upstream cleanup issue

The current upstream removal code clears the entire controller slot with
`memset` before calling `free(connectedControllers[index].reportData)`.
That makes the stored pointer null before the free. When the full native core is
adapted, preserve the report pointer before clearing the slot and free the saved
pointer instead.

This file documents the exact integration points; it does not claim the native
17559 XEX has been hardware-tested yet.
