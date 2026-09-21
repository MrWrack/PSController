#include "plugin_entry.h"

namespace plugin_entry {
static bool g_attached = false;

bool process_attach(const xex_native_entry::Services& services) {
    if (g_attached) return true;
    if (!native_bootstrap::start(services)) return false;
    g_attached = true;
    return true;
}

void process_detach() {
    if (!g_attached) return;
    native_bootstrap::stop();
    g_attached = false;
}

bool attached() { return g_attached; }
}
