#pragma once
#include <stdint.h>

namespace dashlaunch_bridge {

enum Status {
    STATUS_NOT_INITIALIZED = 0,
    STATUS_LAUNCH_NOT_FOUND,
    STATUS_READY
};

struct KernelApi {
    int (*get_module_handle)(const char* module_name, void** module);
    int (*get_procedure_address)(void* module, uint32_t ordinal, void** address);
};

void set_kernel_api(const KernelApi& api);
bool initialize();
void shutdown();
Status status();
void* launch_module();

// Resolve an export from launch.xex by ordinal. Returns 0 safely if launch.xex
// is unavailable or the ordinal is not exported.
void* resolve_launch_export(uint32_t ordinal);

}
