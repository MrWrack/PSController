#pragma once
#include <stdint.h>
#include <stddef.h>
#include "controller_runtime.h"

namespace retail17559_hooks {
typedef bool (*ReadMemoryFn)(uintptr_t, void*, size_t);
typedef bool (*InstallDetourFn)(uintptr_t, void*, void**);
typedef void (*RemoveDetourFn)(uintptr_t);

struct TargetSignature { const uint8_t* bytes; size_t length; };
struct HookApi { ReadMemoryFn read_memory; InstallDetourFn install_detour; RemoveDetourFn remove_detour; };

struct VerifiedSignatures {
    TargetSignature hid_add;
    TargetSignature hid_remove;
};

struct OriginalHooks {
    void* hid_add;
    void* hid_remove;
    void* xinput_read;
    void* xam_caps;
    void* xam_set_state;
};

void bind_hook_api(const HookApi& api);
void bind_verified_signatures(const VerifiedSignatures& signatures);
void clear_verified_signatures();

bool install(const controller_runtime::ResolvedExports& exports,
             void* hid_add_hook, void* hid_remove_hook,
             void* xinput_read_hook, void* xam_caps_hook,
             void* xam_set_state_hook);
void remove();
bool installed();

// Native hook bodies must call through these trampolines for behavior that
// remains owned by the original Xbox/hiddriver path.
const OriginalHooks& originals();

}
