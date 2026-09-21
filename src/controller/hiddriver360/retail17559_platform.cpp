#include "retail17559_platform.h"
#include <string.h>

namespace retail17559_platform {

static NativeApi g_native = {};

static bool install_hooks(const controller_runtime::ResolvedExports& exports) {
    return retail17559_hooks::install(
        exports,
        g_native.hid_add_hook,
        g_native.hid_remove_hook,
        g_native.xinput_read_hook,
        g_native.xam_caps_hook,
        g_native.xam_set_state_hook);
}

static void remove_hooks() {
    retail17559_hooks::remove();
}

bool bind(const NativeApi& api) {
    if (!api.kernel_build || !api.get_module || !api.get_proc ||
        !api.read_memory || !api.install_detour || !api.remove_detour ||
        !api.hid_add_hook || !api.hid_remove_hook ||
        !api.xinput_read_hook || !api.xam_caps_hook || !api.xam_set_state_hook) {
        return false;
    }

    g_native = api;

    retail17559_hooks::HookApi hook_api = {};
    hook_api.read_memory = api.read_memory;
    hook_api.install_detour = api.install_detour;
    hook_api.remove_detour = api.remove_detour;
    retail17559_hooks::bind_hook_api(hook_api);

    controller_startup::PlatformApi startup = {};
    startup.kernel_build = api.kernel_build;
    startup.get_module = api.get_module;
    startup.get_proc = api.get_proc;
    startup.install_verified_17559_hooks = install_hooks;
    startup.remove_hooks = remove_hooks;
    controller_startup::bind_platform_api(startup);
    return true;
}

void unbind() {
    retail17559_hooks::remove();
    controller_startup::PlatformApi empty = {};
    controller_startup::bind_platform_api(empty);
    retail17559_hooks::HookApi empty_hooks = {};
    retail17559_hooks::bind_hook_api(empty_hooks);
    memset(&g_native, 0, sizeof(g_native));
}

}
