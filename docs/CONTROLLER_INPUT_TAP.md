# Controller input tap

This module is the integration point between the normal HID input callback and
PSController's audio/jack detection.

Call:

```cpp
playstation_input_tap::observe(handle, vid, pid, report, length);
```

from the same successful USB interrupt completion that already forwards the
report to the controller mapping code.

The call is observational only:

1. the original report remains unchanged;
2. normal controller mapping still runs;
3. failure to parse audio/jack state does not fail controller input;
4. only standard wired DualSense (054C:0CE6) currently enters the verified
   DualSense jack parser;
5. DS4 and DualSense Edge remain untouched until their jack-state layouts are
   separately verified.

This separation is deliberate because controller functionality must remain
normal in every audio mode.
