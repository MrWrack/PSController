# Xbox 360 voice / Party Chat research boundary

Public Microsoft-era material confirms that Xbox 360 had XHV2, the XAudio2-backed successor to XHV, for Xbox 360 voice functionality. Public XInput documentation also establishes the controller-headset model: a controller headset exposes both capture (microphone) and render (headphone) device identities.

That is enough to guide PSController's architecture, but it is not enough to invent an undocumented dashboard Party Chat registration call.

Implemented now:
- controller AUX microphone capture
- DS4 16 kHz mono chat-format path
- DualSense 48 kHz capture downmix + 48->16 kHz voice conversion
- Party Chat adapter boundary
- return-chat PCM boundary
- safe failure when no verified Xbox voice adapter is installed

Still required before Party Chat can be called working:
- verified 17559/Xam/XHV2 headset registration mechanism
- signed-in user/controller association
- native voice packet/capture submission contract
- dashboard microphone-indicator test
- Xbox Live Party receive/transmit test

No guessed ordinals or private structure layouts should be added merely to make the build compile.
