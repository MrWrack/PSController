# DS4 / DualSense AUX playback path

Primary PSController audio target:

Xbox 360 game/chat PCM -> PSController -> USB isochronous playback -> DualShock 4 or DualSense -> controller 3.5 mm TRRS jack -> headset

The AUX session now joins the existing descriptor probe, isochronous stream wrapper and double-buffered PCM engine.

It intentionally refuses to guess max packet size, interval, alternate setting or PCM format. Those values must come from the real controller USB audio descriptors observed during the 17559 hardware test.

Next hardware-dependent step:
1. capture the controller audio streaming descriptor
2. record alternate setting, endpoint, max packet size and interval
3. record supported PCM format/sample rate/channels
4. populate StreamConfig
5. open playback endpoint
6. send a controlled test PCM signal
7. verify clean disconnect/reconnect

Controller HID remains independent and must survive every AUX failure.
