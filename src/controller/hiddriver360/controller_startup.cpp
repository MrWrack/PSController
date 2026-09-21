#include "controller_startup.h"
#include <string.h>

namespace controller_startup {

static PlatformApi g_api = {};
static bool g_active = false;
static controller_runtime::InitResult g_last =
    controller_runtime::INIT_NATIVE_HOOKS_NOT_BOUND;

void bind_platform_api(const PlatformApi& api) {
    g_api = api;
}

bool initialize() {
    if (g_active) return true;

    if (!g_api.kernel_build || !g_api.get_module || !g_api.get_proc ||
        !g_api.install_verified_17559_hooks) {
        g_last = controller_runtime::INIT_NATIVE_HOOKS_NOT_BOUND;
        return false;
    }

    if (g_api.kernel_build() != 17559) {
        g_last = controller_runtime::INIT_UNSUPPORTED_KERNEL;
        return false;
    }

    controller_runtime::bind_loader_api(g_api.get_module, g_api.get_proc);

    controller_runtime::ResolvedExports exports = {};
    g_last = controller_runtime::resolve_17559_exports(&exports);
    if (g_last != controller_runtime::INIT_OK) return false;

    // The platform hook installer must verify its 17559 targets before writing
    // any branch/detour. Failure leaves the controller subsystem inactive.
    if (!g_api.install_verified_17559_hooks(exports)) {
        g_last = controller_runtime::INIT_NATIVE_HOOKS_NOT_BOUND;
        return false;
    }

    g_active = true;
    return true;
}

void shutdown() {
    if (!g_active) return;
    if (g_api.remove_hooks) g_api.remove_hooks();
    g_active = false;
}

bool active() {
    return g_active;
}

controller_runtime::InitResult last_result() {
    return g_last;
}

}
