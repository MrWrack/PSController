#include "dashlaunch_bridge.h"

namespace {
dashlaunch_bridge::KernelApi g_api = {};
dashlaunch_bridge::Status g_status = dashlaunch_bridge::STATUS_NOT_INITIALIZED;
void* g_launch = 0;
}

namespace dashlaunch_bridge {

void set_kernel_api(const KernelApi& api) {
    g_api = api;
}

bool initialize() {
    g_launch = 0;
    g_status = STATUS_NOT_INITIALIZED;

    if (!g_api.get_module_handle || !g_api.get_procedure_address)
        return false;

    if (g_api.get_module_handle("launch.xex", &g_launch) != 0 || !g_launch) {
        g_status = STATUS_LAUNCH_NOT_FOUND;
        g_launch = 0;
        return false;
    }

    g_status = STATUS_READY;
    return true;
}

void shutdown() {
    g_launch = 0;
    g_status = STATUS_NOT_INITIALIZED;
}

Status status() { return g_status; }
void* launch_module() { return g_launch; }

void* resolve_launch_export(uint32_t ordinal) {
    if (g_status != STATUS_READY || !g_launch ||
        !g_api.get_procedure_address)
        return 0;

    void* address = 0;
    if (g_api.get_procedure_address(g_launch, ordinal, &address) != 0)
        return 0;
    return address;
}

}
