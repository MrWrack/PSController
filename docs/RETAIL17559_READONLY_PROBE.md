# Retail 17559 read-only HID target probe

Before enabling the HID detours, PSController needs verified bytes from the
retail 17559 targets used by upstream hiddriver360:

- HID add: `0x800E4D68`
- HID remove: `0x800E4D28`

`retail17559_probe` is deliberately read-only. It accepts the existing safe
memory-reader callback and copies 4-32 bytes from each target into a diagnostic
snapshot.

It does **not**:

- write kernel memory,
- install hooks,
- create a signature automatically,
- treat one console dump as sufficient proof for every 17559 image.

The collected bytes can be compared with the exact target code/disassembly and
with multiple known-good 17559 consoles before populating
`VerifiedSignatures`. Until that verification is complete, the hook installer
continues to fail closed with `STATUS_SIGNATURE_NOT_CONFIGURED`.

This gives the first hardware diagnostic build a safe way to gather the missing
evidence without bypassing the signature guard.
