# Native original call-through

`retail17559_hooks` now preserves every trampoline returned by the detour
installer. This helper gives each native hook body a narrow typed accessor.

Example pattern:

```cpp
typedef int (*OriginalFn)(/* exact verified native arguments */);
OriginalFn original = native_originals::hid_remove<OriginalFn>();
if (!original)
    return /* safe failure */;
return original(/* original arguments */);
```

Do not invent function signatures in this generic layer. The exact typedef must
live beside the adapted upstream hook where its ABI is known.

This is especially important for the hiddriver360 integration: HID add/remove
and XAM/XInput hooks call their originals for devices or operations they do not
fully own. Losing that call-through can break normal Xbox controller behavior.

The trampoline storage is cleared on rollback/removal, so hook bodies must not
cache these pointers past shutdown.

This helper does not activate any retail-17559 hook. Installation still fails
closed unless verified HID target signatures are supplied.
