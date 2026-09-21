# DashLaunch 3.21 integration

Target: Xbox 360 kernel/dashboard 17559.

DashLaunch 3.21 supports 17559 and can load resident XEX plugins from the [Plugins] section of launch.ini. PSController is intended to be one such plugin.

The platform bridge deliberately does not hard-code undocumented launch.xex ordinals. It first resolves launch.xex through the Xbox module loader and exposes a guarded ordinal resolver. An ordinal is only added to PSController after its meaning and signature are verified against the DashLaunch 3.21 source/examples.

Boot safety:
- failure to find launch.xex returns false
- no guessed function address is called
- Party Chat/audio remains optional
- controller HID must continue even when audio or DashLaunch helper integration fails
- the user's normal DashLaunch plugin-bypass recovery remains usable

Example launch.ini target:

[Plugins]
plugin1 = Hdd:\\PSController\\PSController.xex

The exact storage path can be changed by the user.

Do not bundle DashLaunch binaries or proprietary Xbox SDK files into PSController.
