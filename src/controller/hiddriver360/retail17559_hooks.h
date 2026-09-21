#pragma once
#include <stdint.h>
#include <stddef.h>
#include "controller_runtime.h"

namespace retail17559_hooks {
typedef bool (*ReadMemoryFn)(uintptr_t, void*, size_t);
typedef bool (*InstallDetourFn)(uintptr_t, void*, void**);
typedef void (*RemoveDetourFn)(uintptr_t);

struct TargetSignature {
    const uint8_t* bytes;
    const uint8_t* mask; // 0 = ignore byte, nonzero = compare byte
    size_t length;
};
struct HookApi { ReadMemoryFn read_memory; InstallDetourFn install_detour; RemoveDetourFn remove_detour; };

struct VerifiedSignatures { TargetSignature hid_add; TargetSignature hid_remove; };
struct OriginalHooks {
    void* hid_add; void* hid_remove; void* xinput_read;
    void* xam_caps; void* xam_set_state;
};

enum InstallStatus {
    STATUS_NOT_ATTEMPTED = 0,
    STATUS_OK,
    STATUS_ALREADY_INSTALLED,
    STATUS_API_MISSING,
    STATUS_HOOK_BODY_MISSING,
    STATUS_EXPORT_MISSING,
    STATUS_SIGNATURE_NOT_CONFIGURED,
    STATUS_HID_ADD_SIGNATURE_MISMATCH,
    STATUS_HID_REMOVE_SIGNATURE_MISMATCH,
    STATUS_DETOUR_INSTALL_FAILED,
    STATUS_DETOUR_NO_TRAMPOLINE
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
InstallStatus last_status();
const OriginalHooks& originals();
}
