# PSController hardware test plan

For each test, record motherboard, kernel, controller model and result.

## Stage 1 — controller
- Plugin loads without freeze.
- Dashboard accepts D-pad, buttons and sticks.
- A game accepts input.
- Disconnect/reconnect works.

## Stage 2 — USB audio enumeration
- DualSense remains usable as a controller.
- Audio interfaces can be detected without freezing the console.
- Removing the controller tears audio down safely.

## Stage 3 — headset
- Headphones connected to controller are detected.
- Speaker stream starts/stops safely.
- Microphone stream starts/stops safely.

## Stage 4 — system audio
- Investigate a stable 17559 game-audio source.
- Route PCM to the headset path.
- Verify latency, underruns and title compatibility.

## Failure rule
If any audio stage fails, disable only the audio subsystem. Controller input must remain active.
