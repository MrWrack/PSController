# DualSense USB jack report parser

The DualSense USB main HID input report uses report ID `0x01` and is 64 bytes.
Linux's current `hid-playstation` implementation models the common DualSense
payload with three status bytes and reads jack state from `status[1]`.

In the 64-byte USB report the common payload begins immediately after the
one-byte report ID. Counting the published structure fields places
`status[1]` at absolute report byte 54.

The headphone and microphone detect bits are active-low. PSController therefore
inverts their meaning when converting the raw report into
`sony_aux_detect::JackState`.

Safety:
- accept only report ID 0x01;
- accept only the expected 64-byte USB report;
- never change controller HID ownership;
- malformed reports do not change AUX state;
- DS4 does not use this parser.

The controller input parser should call
`dualsense_jack_report::parse_and_route(handle, report, length)` after receiving
a valid wired DualSense main input report. The audio router then applies the
existing priority rules independently from gamepad input.
