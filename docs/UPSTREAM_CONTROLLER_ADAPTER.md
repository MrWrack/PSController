# Upstream controller adapter

This layer maps the fields already present in hiddriver360's native
`Controller` and `HidControllerExtension` into PSController's safe observer
core without copying the full upstream callback into the audio subsystem.

For the interrupt callback, populate one `UpstreamControllerView` per
`connectedControllers` entry. Use the controller's device handle, controller
driver, VID/PID, and the driver's interrupt TRB buffer/length. Mark the view
occupied only when the slot really owns a controller, and propagate
`cleanupDone`.

Call `before_input_mapping(..., driverExtension)` after the upstream slot
search has confirmed a valid index and before normal report parsing. Its return
value is diagnostic only: never skip mapping, `currentState` updates, Nintendo
handling, or `UsbdQueueAsyncTransfer` because the observer returned false.

For removal, call `before_controller_cleanup(..., deviceHandle2)` after the
slot has been found and before setting `cleanupDone`, clearing the slot,
deleting the driver extension, or freeing the report buffer.

The adapter is capped at four slots because upstream hiddriver360 currently
uses `connectedControllers[4]`.

This does not activate the unverified retail-17559 absolute detours and does
not claim hardware-tested controller or audio support yet.
