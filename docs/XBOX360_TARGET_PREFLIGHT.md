# Xbox 360 target build preflight

Run `tools\\xbox360-target-preflight.bat` from a Visual Studio Developer
Command Prompt.

This preflight does **not** build a XEX. It verifies that the portable tests
pass, that the target adapter source files are present, and that the first
hardware stage remains diagnostic-only.

The final target build still requires a compatible, legally available Xbox 360
PowerPC/XEX build environment. We intentionally do not commit proprietary SDK
binaries or invent SDK declarations, entry-point ABI, loader constants,
ordinals, or XEX metadata.

The first hardware artifact must remain:

- kernel target 17559,
- read-only HID probe,
- controller hooks OFF,
- audio/voice OFF.

Once the exact target environment is identified, its native translation unit
can implement the three services already defined by `first_xex_adapter`:
kernel-build detection, safe memory reading, and debug-line output.
