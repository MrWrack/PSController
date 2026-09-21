# PCM transfer scaffold

PSController now has a double-buffered PCM transfer engine for the next hardware stage.

The engine does not hard-code Xbox kernel structures. Instead, the Xbox 360 integration layer supplies a queue_iso adapter which can construct the native transfer request and call the same asynchronous USB path used by the 17559 USB driver.

Safety rules:
- only queue after a verified isochronous endpoint is open
- two buffers prevent a caller from overwriting a buffer still owned by USB
- completion releases each buffer
- failed queue leaves the buffer reusable
- stop does not free/reuse a queued buffer before its callback
- audio failure must not affect HID/controller input

Initial priority:
1. DualShock 4 / DualSense 3.5 mm AUX playback
2. AUX microphone capture
3. Sony INZONE H7/H9 dongle playback/microphone
4. game/chat mixing and controls

Actual PCM format, sample rate, alternate setting and packet timing must come from verified USB audio descriptors rather than assumptions.
