# Isochronous stream stage

PSController now has a guarded wrapper for opening and closing Xbox 360 USB isochronous endpoints.

This stage intentionally does **not** queue PCM buffers yet.

Sequence:
1. enumerate and validate descriptors
2. identify playback/capture endpoint
3. open the verified isochronous endpoint
4. close it cleanly on disconnect or failure
5. only after hardware validation, add asynchronous PCM transfers

The wrapper follows the UsbdOpenEndpoint / UsbdQueueCloseEndpoint pattern observed in HidDriver360. The API pointers are supplied by the plugin integration layer rather than hard-coding kernel addresses.

A failed endpoint open returns false and must leave controller HID operational.
