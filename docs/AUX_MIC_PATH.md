# DS4 / DualSense AUX microphone path

PSController now has the capture-side session for a microphone connected to the controller 3.5 mm TRRS jack.

Profiles:
- DS4 v2: 16 kHz, mono, signed 16-bit PCM, endpoint 0x82
- DualSense: 48 kHz, stereo/two-channel USB capture, signed 16-bit PCM, endpoint 0x82

The capture session opens the verified ISO IN endpoint and exposes completed PCM to a callback. The final Xbox voice-chat injection/registration layer is still hardware/platform dependent and is intentionally separate.

Safety:
- unsupported VID/PID is rejected
- no capture endpoint means no microphone session
- capture failure never disables controller HID
- disconnect closes the endpoint

Next milestone is native asynchronous ISO-IN queueing and connecting captured microphone PCM to the Xbox 360 voice/chat path.
