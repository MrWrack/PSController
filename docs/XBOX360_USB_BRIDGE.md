# Xbox 360 USB bridge

This layer connects PSController's generic USB-audio descriptor parser to the Xbox 360 retail-kernel USB access pattern used by HidDriver360.

Verified upstream function shapes used as the reference:
- UsbdGetInterfaceDescriptor(deviceHandle*)
- UsbdGetEndpointDescriptor(deviceHandle*, index, transferType, direction)
- UsbdOpenEndpoint(...)
- UsbdQueueAsyncTransfer(...)

The first PSController implementation is deliberately read-only: it retrieves interface information and probes isochronous IN/OUT endpoint descriptors. It does not open an audio endpoint or queue audio transfers yet.

This keeps the first hardware test low-risk. Once descriptor detection is verified on kernel 17559 with DualShock 4, DualSense and INZONE H7/H9 hardware, streaming can be added separately.

Source/reference: EinTim23/hiddriver360 (GPL-3.0). Preserve applicable GPL notices when upstream code is incorporated.
