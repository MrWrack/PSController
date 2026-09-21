# Verified Sony USB audio profiles

These profiles are reference values, not blind overrides. PSController should compare them with descriptors read from the attached controller before opening an audio stream.

## DualShock 4 v2 — VID 054C PID 09CC

Playback:
- interface 1, alternate setting 1
- endpoint 0x01 OUT
- PCM, 2 channels, 16-bit, 32000 Hz
- max packet 132 bytes
- interval 4

Capture:
- interface 2, alternate setting 1
- endpoint 0x82 IN
- PCM, 1 channel, 16-bit, 16000 Hz
- max packet 34 bytes
- interval 4

## DualSense — VID 054C PID 0CE6

Playback:
- interface 1, alternate setting 1
- endpoint 0x01 OUT
- PCM, 4 channels, 16-bit, 48000 Hz
- max packet 392 bytes
- interval 4

Capture:
- interface 2, alternate setting 1
- endpoint 0x82 IN
- PCM, 2 channels, 16-bit, 48000 Hz
- max packet 196 bytes
- interval 4

The DualSense four-channel playback stream includes more than ordinary stereo headset audio, so PSController must perform correct channel routing rather than simply duplicating arbitrary PCM into all four channels.

Unknown controller revisions remain descriptor-first and must not inherit one of these profiles solely because they are made by Sony.
