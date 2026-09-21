# Upstream controller foundation

PSController uses the controller research/design from HidDriver360:
https://github.com/EinTim23/hiddriver360

Verified upstream static Sony USB IDs:
- Sony VID: 0x054C
- DualShock 4 v1: 0x05C4
- DualShock 4 v2: 0x09CC
- DualShock 4 Wireless Adapter: 0x0BA0
- DualSense: 0x0CE6
- DualSense Edge: 0x0DF2

Upstream maps PlayStation face buttons to Xbox-style A/B/X/Y fields and supports Xbox 360 retail dashboard 17559.

HidDriver360 is GPL-3.0. Any incorporated/modified GPL code must retain the applicable license and notices. Proprietary Xbox SDK/XDK files must not be committed.

## PSController integration rule

Controller input is the stable path. Headset/audio is optional. Failure to discover or initialize a controller audio interface must never disable the HID/controller path.
