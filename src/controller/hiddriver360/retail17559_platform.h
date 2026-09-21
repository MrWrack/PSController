#pragma once
#include "controller_startup.h"
#include "retail17559_hooks.h"

namespace retail17559_platform {

// Bind only platform primitives supplied by the real XEX entry layer.
// Hook targets themselves stay inside the guarded 17559 hook module.
struct NativeApi {
    unsigned short (*kernel_build)();
    controller_runtime::GetModuleHandleFn get_module;
    controller_runtime::GetProcedureAddressFn get_proc;
    retail17559_hooks::ReadMemoryFn read_memory;
    retail17559_hooks::InstallDetourFn install_detour;
    retail17559_hooks::RemoveDetourFn remove_detour;

    void* hid_add_hook;
    void* hid_remove_hook;
    void* xinput_read_hook;
    void* xam_caps_hook;
    void* xam_set_state_hook;
};

bool bind(const NativeApi& api);
void unbind();

}
