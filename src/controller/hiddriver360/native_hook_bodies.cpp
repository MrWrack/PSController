#include "native_hook_bodies.h"
#include <string.h>

namespace native_hook_bodies {
static RuntimeApi g_runtime = {};

void bind_runtime(const RuntimeApi& api) {
    g_runtime = api;
}

void observe_interrupt(void* driver_extension) {
    if (!driver_extension || !g_runtime.snapshot) return;

    ControllerSnapshot snapshot = {};
    if (!g_runtime.snapshot(&snapshot) ||
        snapshot.count == 0 || snapshot.count > 4) return;

    (void)interrupt_observer_patch::before_mapping(
        snapshot.views, snapshot.count, driver_extension);
}

int hid_remove(void* device_handle) {
    if (!device_handle) return 0;

    ControllerSnapshot snapshot = {};
    bool owned = false;

    if (g_runtime.snapshot &&
        g_runtime.snapshot(&snapshot) &&
        snapshot.count > 0 && snapshot.count <= 4) {
        for (uint32_t i = 0; i < snapshot.count; ++i) {
            if (snapshot.views[i].occupied &&
                snapshot.views[i].device_handle == device_handle) {
                interrupt_observer_patch::before_cleanup(
                    snapshot.views, snapshot.count, device_handle);
                owned = true;
                break;
            }
        }
    }

    if (owned && g_runtime.remove_owned) {
        g_runtime.remove_owned(device_handle);
        return 0;
    }

    HidRemoveOriginal original =
        native_originals::hid_remove<HidRemoveOriginal>();
    if (!original) return 0;
    return original(device_handle);
}

}
