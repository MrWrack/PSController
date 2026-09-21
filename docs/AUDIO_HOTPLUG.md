# Audio hot-plug routing

PSController now has a device-presence layer intended to sit behind the Xbox 360 USB/HID add/remove callbacks.

Routing policy:
1. INZONE H5/H7/H9 dongle, when verified and active
2. DS4/DualSense controller AUX
3. no plugin audio route

Connecting an INZONE dongle while a PlayStation controller remains connected must not replace or disconnect controller input. It only changes the preferred audio route. Removing INZONE falls back to controller AUX if that route is still present.

The upstream HidDriver360 code confirms separate HidAddDevice/HidRemoveDevice hooks and exposes the device handle used by its USB path. PSController's hot-plug layer accepts that handle but does not yet patch those hooks directly.

Important: an INZONE device must not be marked as H5/H7/H9 solely because it exposes USB Audio. Its model identity must first be verified from the real transceiver descriptors. Until then, the hot-plug router remains ready but will not falsely claim an unknown dongle.
