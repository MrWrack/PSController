# First-test build identity

To avoid confusion between future runtime builds and the initial hardware
diagnostic, the repository now has an explicit first-test build identity.

- Project: **PSController**
- Target kernel: **17559**
- Mode: **diagnostic-only**
- HID hooks: **disabled**
- Audio: **disabled**

`build_info::first_test()` exposes these values to the eventual native logger
or build-specific shim without requiring Xbox SDK headers.

`tools/first-test-preflight.bat` gives the Windows PC a simple prerequisite
check. It does not pretend to build an XEX and does not install anything.

The next build-specific step remains selecting/validating the compatible Xbox
360 target compiler/linker/XEX environment. Once that environment is known,
the native DllMain translation unit can implement the existing
`xex_shim_contract`.
