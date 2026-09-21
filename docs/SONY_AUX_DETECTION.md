# Sony AUX jack detection

PSController must switch AUX routes only from a verified physical jack state.

## DualSense

Public DualSense implementations report separate headphone and microphone
connection state for the 3.5 mm jack. Linux support also treats DualSense jack
detection as controller/HID-provided state associated with the USB audio
device rather than assuming that an audio endpoint alone proves a headset is
inserted.

PSController therefore uses `sony_aux_detect::on_verified_jack_state()` as
the boundary between a Sony-specific report parser and the generic audio
router.

## DualShock 4

Do not reuse a DualSense byte offset or mask for DS4. DS4 gets its own verified
parser once the exact wired report field is established on the target
controller revision.

## Safety rule

Unknown or malformed reports do nothing. No guessed bit can disable,
disconnect, reopen, or otherwise alter controller HID input.

Routing after a verified state event remains:

- USB headset: game audio + Party Chat + Game Chat, USB headset mic.
- Controller AUX: game audio + Party Chat + Game Chat, AUX mic.
- Bare DualSense: Party Chat + Game Chat only, built-in mic.
- Bare DS4: no built-in microphone fallback.
