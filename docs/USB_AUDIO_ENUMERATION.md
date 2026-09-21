# USB audio enumeration

PSController uses descriptor-first discovery for controller AUX and USB headset audio.

## Detection

A candidate USB device is inspected for:
- Audio class interface (0x01)
- Audio Control subclass (0x01)
- Audio Streaming subclass (0x02)
- isochronous OUT endpoints for playback
- isochronous IN endpoints for microphone/capture

Endpoint numbers are not guessed or hard-coded before hardware verification.

## Targets

The same discovery layer is intended to feed:
- DualShock 4 3.5 mm AUX/TRRS
- DualSense 3.5 mm AUX/TRRS
- DualSense USB audio
- Sony INZONE H7/H9 USB transceiver

## Safety

Enumeration must be read-only until a complete supported layout is recognized. A malformed or unsupported USB descriptor must cause that audio backend to be ignored, not crash PSController or disable controller HID input.
