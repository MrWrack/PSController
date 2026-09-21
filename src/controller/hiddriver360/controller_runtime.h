#pragma once
#include <stdint.h>

namespace controller_runtime {

enum InitResult {
    INIT_OK = 0,
    INIT_UNSUPPORTED_KERNEL,
    INIT_MISSING_KERNEL,
    INIT_MISSING_XAM,
    INIT_MISSING_REQUIRED_EXPORT,
    INIT_NATIVE_HOOKS_NOT_BOUND
};

struct ResolvedExports {
    void* usbd_get_device_descriptor;
    void* usbd_get_endpoint_descriptor;
    void* usbd_add_device_complete;
    void* usbd_open_default_endpoint;
    void* usbd_open_endpoint;
    void* usbd_get_device_speed;
    void* usbd_queue_async_transfer;
    void* usbd_queue_close_endpoint;
    void* usbd_queue_close_default_endpoint;
    void* usbd_remove_device_complete;
    void* mm_free_physical_memory;
    void* xinputd_read_state;
    void* xam_input_get_capabilities_ex;
    void* xam_input_set_state;
};

typedef void* (*GetModuleHandleFn)(const char* name);
typedef int (*GetProcedureAddressFn)(void* module, uint32_t ordinal, void** out);

void bind_loader_api(GetModuleHandleFn get_module,
                     GetProcedureAddressFn get_proc);

// Safe first stage: resolve documented-by-upstream 17559 imports only.
// It deliberately does not patch absolute addresses or reset the USB driver.
InitResult resolve_17559_exports(ResolvedExports* out);

}
