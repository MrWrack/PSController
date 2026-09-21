# PSController

Experimental Xbox 360 RGH/DashLaunch plugin project by **MrWrack**.

## Target
- Xbox 360 retail kernel/dashboard **2.0.17559.0**
- One plugin output: `PSController.xex`
- DualShock 4 and DualSense over USB
- Controller input available in dashboard and games
- Planned experimental headset support: controller 3.5 mm output, microphone, USB headsets and game/chat mixing

## Base
The controller/HID work is intended to build on [HidDriver360](https://github.com/EinTim23/hiddriver360), which supports retail 17559 and DS4/DualSense USB input.

HidDriver360 is GPL-3.0. PSController therefore keeps derivative work GPL-3.0 and must preserve applicable upstream notices/source availability.

## Development status
**v0.1 scaffold — not a usable XEX yet.**

The audio path is deliberately isolated from controller input. Audio initialization failure must not take down controller input. Full Xbox 360 game-audio capture and DualShock/DualSense headset routing still require implementation and hardware verification.

## Test targets
The same 17559 build is intended to be tested across Corona, Trinity, Jasper and Falcon RGH systems. RGH installation method should not require separate PSController builds.

## Safety / recovery
During early testing, do not rely on an experimental build as an irreplaceable boot plugin. Keep a known recovery path that starts the console with DashLaunch plugins bypassed.

## Build
The upstream driver uses the official Xbox 360 SDK and Visual Studio. Proprietary SDK files are **not** included in this repository.

## Credits
- MrWrack — PSController project
- EinTim23 and HidDriver360 contributors — Xbox 360 HID/controller foundation
