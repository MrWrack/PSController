#include "boot_mode.h"

namespace boot_mode {
static bool g_active = false;
static Mode g_mode = MODE_DIAGNOSTIC_ONLY;

bool start(const Config& config, const Api& api) {
    if (g_active) return true;
    g_mode = config.mode;

    if (config.mode == MODE_DIAGNOSTIC_ONLY) {
        const uint32_t n = config.probe_bytes ? config.probe_bytes : 16;
        if (diagnostic_boot::run(api.diagnostic, n) != diagnostic_boot::RESULT_OK)
            return false;
        g_active = true;
        return true;
    }

    if (!plugin_entry::process_attach(api.native_services))
        return false;

    g_active = true;
    return true;
}

void stop() {
    if (!g_active) return;
    if (g_mode == MODE_CONTROLLER_RUNTIME)
        plugin_entry::process_detach();
    g_active = false;
    g_mode = MODE_DIAGNOSTIC_ONLY;
}

Mode active_mode() { return g_mode; }
bool active() { return g_active; }
}
