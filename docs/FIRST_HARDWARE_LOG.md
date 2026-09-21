# First hardware log

The first-test lifecycle now exposes explicit log stages around the existing
read-only probe.

Expected first-run sequence:

```text
PSController: first-test entry starting
PSController: diagnostic-only mode; hooks/audio disabled
HID_ADD @800E4D68: ...
HID_REMOVE @800E4D28: ...
PSController: diagnostic capture complete; no hooks installed
```

If the read or platform callback fails:

```text
PSController: startup failed safely
```

The diagnostic mode does not claim DualSense/DS4 input or audio is working. Its
purpose is to prove the plugin can load safely on retail 17559 and to collect
the exact HID target bytes needed for verification.

When a compatible legal Xbox 360 build environment is available, its native
debug-output callback can be supplied as `WriteLineFn`. This file contains no
proprietary SDK dependency.
