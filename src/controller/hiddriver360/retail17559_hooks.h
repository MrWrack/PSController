#pragma once
#include <stdint.h>
#include <stddef.h>
#include "controller_runtime.h"

namespace retail17559_hooks {
typedef bool (*ReadMemoryFn)(uintptr_t, void*, size_t);
typedef bool (*InstallDetourFn)(uintptr_t, void*, void**);
typedef void (*RemoveDetourFn)(uintptr_t);
struct HookApi { ReadMemoryFn read_memory; InstallDetourFn install_detour; RemoveDetourFn remove_detour; };
void bind_hook_api(const HookApi& api);
bool install(const controller_runtime::ResolvedExports& exports, void* hid_add_hook, void* hid_remove_hook, void* xinput_read_hook, void* xam_caps_hook, void* xam_set_state_hook);
void remove();
bool installed();
}
