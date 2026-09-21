# Hardware audio probe milestone

The next PSController hardware milestone is descriptor detection on a real Xbox 360 running kernel 17559.

For each connected target, record:
- target type: DS4 AUX, DualSense AUX or INZONE transceiver
- whether an Audio Control interface was found
- isochronous OUT endpoint address
- isochronous IN endpoint address
- maximum packet size and polling interval from the native descriptor

No audio transfer is started during this milestone.

## Pass condition

A supported device can be connected and removed without freezing the dashboard, controller HID remains usable, and the descriptor probe reports the same layout consistently after reconnect.

## Failure condition

If no supported audio layout is found, the audio backend stays disabled. Controller input must continue working.

Only after this passes should PSController open isochronous endpoints and begin PCM streaming.
