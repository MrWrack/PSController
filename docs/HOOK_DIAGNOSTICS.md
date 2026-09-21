# Hook diagnostics

This module turns the guarded retail-17559 hook install status into text that a
debug log or future on-console diagnostics screen can display.

It is intentionally diagnostic-only. A signature mismatch is never converted
into a warning-and-continue path: controller detours remain fail-closed.

Useful first hardware-test states include:

- `signature_not_configured`: expected until verified 17559 signatures exist.
- `hid_add_signature_mismatch` / `hid_remove_signature_mismatch`: do not patch.
- `detour_install_failed`: partial installs are rolled back.
- `detour_no_trampoline`: partial installs are rolled back because native
  call-through cannot be guaranteed.
- `ok`: only means the guarded hook install completed; it does not prove
  controller, AUX, Party Chat, Game Chat, or USB audio works on hardware.

This distinction should remain visible during the first Corona/Trinity/Falcon/
Jasper tests.
