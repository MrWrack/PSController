# Native XEX shim checklist

The portable adapter is ready. The final native translation unit is intentionally
not committed with guessed Xbox 360 SDK declarations.

When a compatible target build environment is selected, implement exactly these
three services from its verified headers/API:

- `detect_kernel_build()`
- `safe_read_memory(address, out, size)`
- `debug_write_line(line)`

Then the verified process-attach entry calls
`target_shim_template::attach()`; process detach calls
`target_shim_template::detach()`.

## First hardware build safety gate

Before producing the first diagnostic XEX, verify all of the following:

- target is Xbox 360 retail kernel 17559,
- build mode remains diagnostic-only,
- controller detours are disabled,
- audio/voice startup is disabled,
- HID target access is read-only,
- debug output is available,
- plugin can be bypassed through DashLaunch recovery.

Do not enable plugin5 until the XEX has been built from the verified target
environment and the diagnostic entry has been reviewed.
