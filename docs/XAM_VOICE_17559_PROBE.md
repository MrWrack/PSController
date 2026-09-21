# 17559 XAM voice diagnostic stage

A useful public reverse-engineering reference, PcMic-360, contains a RuntimeHost probe naming three Xbox voice functions:

- XamVoiceCreate
- XamVoiceClose
- XamVoiceHeadsetPresent

Its probe also demonstrates observing headset-state changes. This is materially closer to PSController's dashboard Party Chat target than treating XHV2 alone as a global dashboard API.

Important limitation: that project contains build-specific absolute addresses/stubs. PSController deliberately does **not** copy those addresses into the production plugin. An address that is correct for one RuntimeHost/XAM image can crash another build.

PSController now has xam_voice_probe as a read-only diagnostic boundary. The probe:
- accepts only function pointers supplied by a verified 17559 platform resolver
- creates a voice object
- samples headset-present state
- closes the object
- does not patch XAM
- does not force headset presence
- does not inject microphone PCM yet

Test sequence once the 17559 resolver is verified:
1. boot with PSController diagnostic mode
2. sample with no Xbox headset
3. connect a known-good Xbox 360 headset and sample again
4. verify headset-present changes
5. repeat with DualSense/DS4 USB + AUX headset
6. only after the state path is proven, implement the virtual-headset/PCM bridge

This keeps the first console test observational and reduces the chance of a dashboard crash.
