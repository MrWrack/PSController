# XEX entry integration

The portable repository now has the lifecycle immediately below `DllMain`:

```text
DllMain(DLL_PROCESS_ATTACH)
  -> construct verified xex_native_entry::Services
  -> plugin_entry::process_attach(services)

DllMain(DLL_PROCESS_DETACH)
  -> plugin_entry::process_detach()
```

The actual XDK-facing `DllMain` must live in a build-environment-specific
translation unit. It should contain no controller/audio policy; its job is only
to provide verified native services and call this boundary.

Do not commit proprietary Microsoft SDK/XDK libraries, headers, or binaries.

## Required before calling process_attach

- kernel build provider
- module/export resolver
- safe memory reader
- detour installer/remover
- exact native HID add/remove hook bodies
- exact XInput/XAM hook bodies
- verified retail-17559 HID target signatures

If any of these are missing, do not fabricate a service implementation.
The guarded startup is designed to fail rather than patch an unknown target.

## Test-build milestone

Once those native pieces are supplied by the legal build environment, the
portable lifecycle is complete enough to attempt a controller-only diagnostic
XEX. AUX, Party Chat, Game Chat, system/game audio and wireless headset audio
remain separate later milestones and must not be reported as working merely
because the XEX loads.
