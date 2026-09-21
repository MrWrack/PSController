# Controller AUX / 3.5 mm headset support

PSController has a separate path for a wired 3.5 mm TRRS headset connected directly to a supported PlayStation controller.

Target path:

Xbox 360 -> PSController.xex -> USB -> DualShock 4 / DualSense -> 3.5 mm AUX/TRRS headset

Planned support:
- stereo game audio
- voice/chat audio
- headset microphone
- headset detection
- volume control
- microphone mute
- game/chat mix where the Xbox audio routing can provide separate streams

This is separate from Sony INZONE H7/H9 USB-transceiver support.

The Xbox 360 does not receive the analog AUX signal directly. PSController must use the controller's USB audio/control interfaces. Endpoint/interface values will only be added after they are verified on real hardware.

Audio remains optional: AUX initialization failure must never stop controller input.
