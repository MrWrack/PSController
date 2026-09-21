# Target entry contract

This layer gives the future SDK/toolchain-specific XEX entry point a small,
testable contract without inventing Xbox loader ABI details.

The native shim maps its verified process attach/detach reason values to
`EntryEvent`. The portable contract then:

- requires services on process attach,
- runs the first diagnostic adapter,
- accepts only a successful 17559 diagnostic attach,
- performs portable cleanup on process detach,
- leaves unknown/thread events untouched.

A host-side test is included so this logic can be checked before any XEX is
produced. The test uses synthetic readable bytes only; it is not an Xbox
hardware test.
