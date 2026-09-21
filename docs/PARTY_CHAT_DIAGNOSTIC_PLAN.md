# Party Chat diagnostic plan

The next PSController hardware test should establish the Xbox 360's real headset state before attempting microphone injection.

Public PcMic-360 research provides two useful leads:
- a resolver path for ordinal 0x2B1, labelled MicDeviceRequest
- observed voice functions including XVoicedHeadsetPresent, XVoicedActivate, XVoicedSubmitPacket and XVoicedClose

Those names/addresses are research leads, not yet production contracts. PSController does not copy the reference project's absolute addresses.

## Three-state test

Capture the same diagnostic fields in three phases:

1. NO_HEADSET
   - no headset connected
   - establishes baseline

2. XBOX_HEADSET
   - connect a known-good native Xbox 360 headset
   - establishes what the dashboard considers a real headset

3. PLAYSTATION_AUX
   - DS4 or DualSense connected over USB
   - headset connected to its 3.5 mm jack
   - compare against the native Xbox headset state

Record:
- xam.xex resolved
- MicDeviceRequest ordinal resolved
- voice API available
- voice object created
- headset-present result

Success criterion for this stage:
The native Xbox headset must produce a repeatable state change from NO_HEADSET. Only then is it meaningful to compare the PlayStation AUX path.

This diagnostic does not transmit voice, patch XAM, or fake headset presence. The microphone indicator in Party Chat remains a later milestone after the headset state and submit path are verified.
