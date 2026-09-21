# Voice discovery on 17559

Public reverse-engineering work in PcMic-360 provides a useful lead beyond the earlier XamVoiceCreate / Close / HeadsetPresent observation.

Its current probe resolves kernel/XAM-related ordinal 0x2B1 and labels the target MicDeviceRequest while scanning XAM call sites. That is useful evidence for microphone-device discovery, but it does not establish a safe calling convention for PSController.

PSController therefore adds a discovery-only resolver:
- locate xam.xex through XexGetModuleHandle
- resolve ordinal 0x2B1 through XexGetProcedureAddress
- optionally validate the returned address
- record whether the function is present
- do NOT call it yet

This is deliberately safer than copying absolute addresses such as the RuntimeHost-specific addresses seen in PcMic-360.

The next hardware diagnostic should report only:
- xam.xex found / not found
- ordinal 0x2B1 resolved / not resolved
- resolved pointer validity

Only after the exact signature and behavior are verified on 17559 should PSController invoke the microphone-device request path or connect it to the Party Chat bridge.
