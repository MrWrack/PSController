# Controller runtime startup safety

Upstream hiddriver360's 17559 retail startup combines two different classes of
integration:

1. kernel/XAM exports resolved by ordinal;
2. build-specific absolute addresses and direct memory patches, followed by a
   full USB driver reset.

PSController now separates those stages.

`controller_runtime::resolve_17559_exports()` implements only the first stage.
It resolves the same kernel/XAM ordinals used by upstream and fails closed if
any required export is unavailable.

It intentionally does **not** yet execute upstream's absolute retail addresses,
write branch/NOP patches, or call the USB power-down/re-entry sequence. Those
operations can freeze a console if an address is wrong, and must be gated by an
exact 17559 runtime/build verification before installation.

The final plugin startup order should be:

1. verify retail kernel build 17559;
2. resolve required exports;
3. verify native hook targets for that exact build;
4. install controller hooks;
5. initialize optional PSController audio/voice;
6. if audio fails, leave controller hooks running;
7. never reset USB merely because optional audio failed.

This preserves the project's main recovery rule: controller functionality is
the primary subsystem; audio/voice is optional and must fail safely.
