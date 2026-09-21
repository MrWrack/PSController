# Interrupt handler merge recipe

This is the intended merge point for upstream hiddriver360's
`interruptHandler` and `HidRemoveDeviceHook`.

## interruptHandler

Keep upstream's driver-extension validation and controller search. Immediately
after the search:

```cpp
if (index < 0)
    return 0;
```

Then prepare four `UpstreamControllerView` entries from
`connectedControllers`. For each occupied slot copy:

- `deviceHandle`
- `controllerDriver`
- `vendorId`
- `productId`
- `controllerDriver->interruptTrb.buffer`
- `controllerDriver->interruptTrb.length`
- `controllerDriver->cleanupDone`

Call:

```cpp
(void)interrupt_observer_patch::before_mapping(
    views, 4, driverExtension);
```

The return value is intentionally ignored. Continue upstream's Nintendo
handshake, HID parsing, mapping, current-state update and transfer requeue.

## HidRemoveDeviceHook

After a matching index is found, create the same views and call:

```cpp
interrupt_observer_patch::before_cleanup(
    views, 4, deviceHandle2);
```

Do this before `cleanupDone = 1`, before clearing the controller slot, and
before deleting/freeing native objects.

Also save `connectedControllers[index].reportData` in a local variable before
the slot is zeroed; free that saved pointer after the slot has been detached.
This fixes the cleanup ordering problem in the upstream code.

## Why this is not a replacement callback yet

The repository does not currently carry all XDK-facing definitions and native
detour machinery needed to compile upstream `main.cpp` unchanged. Keeping this
merge as a narrow adapter avoids inventing ABI details. The final XEX-facing
translation should be added only with the legal compatible build environment
and verified retail-17559 detour signatures.
