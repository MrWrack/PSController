# 17559 probe output

The read-only HID probe can now be formatted into copyable diagnostic lines,
for example:

`HID_ADD @800E4D68: XX XX XX XX ...`

`HID_REMOVE @800E4D28: XX XX XX XX ...`

The formatter does not read or write kernel memory itself. It only formats a
snapshot that was successfully captured by `retail17559_probe`.

For the first hardware run, capture 16 or 32 bytes and preserve both lines
exactly. Do not convert those bytes into an enabled signature until the target
instructions and expected 17559 image have been checked. This keeps the probe
useful even if a console has other plugins loaded.

Upstream hiddriver360 documents retail 17559 support, but PSController keeps its
own signature gate because a bad absolute detour can crash a console.
