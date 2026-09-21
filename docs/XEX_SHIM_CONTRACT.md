# XEX shim contract

This is the contract the final build-toolchain-specific translation unit must
satisfy. It intentionally contains no Xbox SDK headers or guessed ABI.

The native shim supplies only three things to the portable core:

1. detected kernel build,
2. a fully populated `boot_mode::Api`,
3. a debug-line logger.

The portable path then owns validation and the diagnostic-only first-test
policy.

## Final toolchain-specific unit

Once the exact compatible build environment is known, add one translation unit
outside the portable core that:

- includes that environment's real Xbox 360 headers,
- implements kernel build detection,
- implements safe memory read/debug output,
- constructs the already-defined native services,
- calls `xex_shim_contract::process_attach()` on process attach,
- calls `xex_shim_contract::process_detach()` on process detach.

Do not guess function signatures, loader reason constants, import ordinals, or
XEX metadata in advance. Those are build-environment contracts.

## First-XEX behavior remains locked down

Even after this shim is supplied, `native_test_host` still accepts only
kernel 17559 and selects the read-only diagnostic entry. Controller detours and
audio are not activated by the first hardware build.
