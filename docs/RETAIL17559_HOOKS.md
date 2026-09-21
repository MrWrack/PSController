# Retail 17559 guarded hooks

This layer installs the controller detours only after checking the stable
leading instruction bytes at the retail 17559 HID add/remove targets documented
by upstream hiddriver360. XInput/XAM targets come from resolved exports.

All five installed detours are tracked. A partial installation rolls back the
detours already installed, and normal shutdown removes them in reverse order.

No USB-driver reset or direct kernel NOP/branch patch is performed here.
