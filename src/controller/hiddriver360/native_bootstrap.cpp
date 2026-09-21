#include "native_bootstrap.h"
#include "../../pscontroller.h"

namespace native_bootstrap {
static bool g_bound = false;
static bool g_running = false;

bool start(const xex_native_entry::Services& services) {
    if (g_running) return true;

    if (!xex_native_entry::bind(services))
        return false;
    g_bound = true;

    if (!pscontroller::initialize()) {
        xex_native_entry::unbind();
        g_bound = false;
        return false;
    }

    g_running = true;
    return true;
}

void stop() {
    if (g_running) {
        pscontroller::shutdown();
        g_running = false;
    }
    if (g_bound) {
        xex_native_entry::unbind();
        g_bound = false;
    }
}

bool running() { return g_running; }

}
