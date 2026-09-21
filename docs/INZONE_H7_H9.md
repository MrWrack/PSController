# Sony INZONE H7 / H9 support

PSController will include an optional USB-headset path for the Sony INZONE H7 and H9 supplied USB transceiver.

Sony documents that H7/H9 connect to a computer or PlayStation 5 through their supplied USB transceiver using a 2.4 GHz wireless link. Sony also documents game/chat balance and microphone use through the transceiver.

## Planned Xbox 360 path

1. Detect the USB transceiver.
2. Dump and validate its USB descriptors.
3. Discover playback, chat and microphone endpoints.
4. Start streams independently of PlayStation-controller HID.
5. Route Xbox game/chat PCM only after the Xbox audio source is verified.
6. Preserve headset volume, game/chat balance and microphone mute where exposed by the transceiver.

## Important

No undocumented VID/PID or endpoint number is guessed in source. The first H7/H9 hardware test should capture the real USB descriptors. We then add the verified identity and endpoint handling.

If INZONE initialization fails, PSController disables only the INZONE audio path. Controller input remains available.
