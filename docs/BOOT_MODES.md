# Boot modes

PSController now has an explicit split between the first safe hardware probe and
the later controller runtime.

## Diagnostic-only

`MODE_DIAGNOSTIC_ONLY`

- reads the two retail-17559 HID targets,
- emits their bytes through the supplied logger,
- does not call `plugin_entry::process_attach`,
- therefore does not install controller detours,
- does not start audio.

This is the intended first XEX hardware run.

## Controller runtime

`MODE_CONTROLLER_RUNTIME`

Uses the normal guarded plugin lifecycle. This mode is for after the 17559
target bytes/signatures and native hook ABI have been verified.

A build should default to diagnostic-only until those prerequisites are met.
Changing the mode must not silently disable signature validation.

## Why the split exists

A diagnostic XEX can load on the console and gather the missing target evidence
without requiring us to guess bytes or enable the experimental hooks first.
After the results are reviewed, the same lifecycle can move to controller
runtime without changing the audio/controller policy code.
