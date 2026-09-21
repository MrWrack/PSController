#include "controller_runtime.h"
#include <string.h>

namespace controller_runtime {

static GetModuleHandleFn g_get_module = 0;
static GetProcedureAddressFn g_get_proc = 0;

void bind_loader_api(GetModuleHandleFn get_module,
                     GetProcedureAddressFn get_proc) {
    g_get_module = get_module;
    g_get_proc = get_proc;
}

static bool resolve(void* module, uint32_t ordinal, void** out) {
    if (!module || !out || !g_get_proc) return false;
    *out = 0;
    return g_get_proc(module, ordinal, out) >= 0 && *out != 0;
}

InitResult resolve_17559_exports(ResolvedExports* out) {
    if (!out) return INIT_MISSING_REQUIRED_EXPORT;
    memset(out, 0, sizeof(*out));
    if (!g_get_module || !g_get_proc) return INIT_NATIVE_HOOKS_NOT_BOUND;

    void* kernel = g_get_module("xboxkrnl.exe");
    if (!kernel) return INIT_MISSING_KERNEL;
    void* xam = g_get_module("xam.xex");
    if (!xam) return INIT_MISSING_XAM;

    // Ordinals used by upstream hiddriver360 on retail 17559.
    if (!resolve(kernel, 759, &out->usbd_get_device_descriptor) ||
        !resolve(kernel, 744, &out->usbd_get_endpoint_descriptor) ||
        !resolve(kernel, 740, &out->usbd_add_device_complete) ||
        !resolve(kernel, 746, &out->usbd_open_default_endpoint) ||
        !resolve(kernel, 747, &out->usbd_open_endpoint) ||
        !resolve(kernel, 742, &out->usbd_get_device_speed) ||
        !resolve(kernel, 748, &out->usbd_queue_async_transfer) ||
        !resolve(kernel, 750, &out->usbd_queue_close_endpoint) ||
        !resolve(kernel, 749, &out->usbd_queue_close_default_endpoint) ||
        !resolve(kernel, 751, &out->usbd_remove_device_complete) ||
        !resolve(kernel, 189, &out->mm_free_physical_memory) ||
        !resolve(kernel, 486, &out->xinputd_read_state) ||
        !resolve(xam, 685, &out->xam_input_get_capabilities_ex) ||
        !resolve(xam, 402, &out->xam_input_set_state)) {
        memset(out, 0, sizeof(*out));
        return INIT_MISSING_REQUIRED_EXPORT;
    }

    return INIT_OK;
}

}
