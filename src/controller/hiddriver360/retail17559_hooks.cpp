#include "retail17559_hooks.h"
#include <string.h>

namespace retail17559_hooks {
static HookApi g_api = {};
static VerifiedSignatures g_signatures = {};
static OriginalHooks g_originals = {};
static bool g_installed = false;
static InstallStatus g_status = STATUS_NOT_ATTEMPTED;
static uintptr_t g_targets[5] = {0,0,0,0,0};

static const uintptr_t HID_ADD = 0x800E4D68u;
static const uintptr_t HID_REMOVE = 0x800E4D28u;

static bool valid_signature(const TargetSignature& s) {
    return s.bytes && s.mask && s.length >= 4 && s.length <= 32;
}

static bool match(uintptr_t address, const TargetSignature& signature) {
    if (!g_api.read_memory || !valid_signature(signature)) return false;
    uint8_t actual[32] = {};
    if (!g_api.read_memory(address, actual, signature.length)) return false;
    for (size_t i = 0; i < signature.length; ++i) {
        if (signature.mask[i] && actual[i] != signature.bytes[i]) return false;
    }
    return true;
}

void bind_hook_api(const HookApi& api) { g_api = api; }
void bind_verified_signatures(const VerifiedSignatures& signatures) { g_signatures = signatures; }
void clear_verified_signatures() { memset(&g_signatures, 0, sizeof(g_signatures)); }

static void clear_runtime_state() {
    memset(g_targets, 0, sizeof(g_targets));
    memset(&g_originals, 0, sizeof(g_originals));
}

static void rollback() {
    if (g_api.remove_detour) {
        for (int i = 4; i >= 0; --i)
            if (g_targets[i]) g_api.remove_detour(g_targets[i]);
    }
    clear_runtime_state();
}

bool install(const controller_runtime::ResolvedExports& e,
             void* ha, void* hr, void* xi, void* xc, void* xs) {
    if (g_installed) { g_status = STATUS_ALREADY_INSTALLED; return true; }
    g_status = STATUS_NOT_ATTEMPTED;

    if (!g_api.install_detour || !g_api.read_memory || !g_api.remove_detour) {
        g_status = STATUS_API_MISSING; return false;
    }
    if (!ha || !hr || !xi || !xc || !xs) {
        g_status = STATUS_HOOK_BODY_MISSING; return false;
    }
    if (!e.xinputd_read_state || !e.xam_input_get_capabilities_ex ||
        !e.xam_input_set_state) {
        g_status = STATUS_EXPORT_MISSING; return false;
    }
    if (!valid_signature(g_signatures.hid_add) ||
        !valid_signature(g_signatures.hid_remove)) {
        g_status = STATUS_SIGNATURE_NOT_CONFIGURED; return false;
    }
    if (!match(HID_ADD, g_signatures.hid_add)) {
        g_status = STATUS_HID_ADD_SIGNATURE_MISMATCH; return false;
    }
    if (!match(HID_REMOVE, g_signatures.hid_remove)) {
        g_status = STATUS_HID_REMOVE_SIGNATURE_MISMATCH; return false;
    }

    uintptr_t targets[5] = { HID_ADD, HID_REMOVE,
        (uintptr_t)e.xinputd_read_state,
        (uintptr_t)e.xam_input_get_capabilities_ex,
        (uintptr_t)e.xam_input_set_state };
    void* hooks[5] = {ha, hr, xi, xc, xs};
    void** outs[5] = {&g_originals.hid_add, &g_originals.hid_remove,
        &g_originals.xinput_read, &g_originals.xam_caps,
        &g_originals.xam_set_state};

    clear_runtime_state();
    for (int i = 0; i < 5; ++i) {
        void* original = 0;
        if (!g_api.install_detour(targets[i], hooks[i], &original)) {
            g_status = STATUS_DETOUR_INSTALL_FAILED; rollback(); return false;
        }
        g_targets[i] = targets[i];
        if (!original) {
            g_status = STATUS_DETOUR_NO_TRAMPOLINE; rollback(); return false;
        }
        *outs[i] = original;
    }

    g_installed = true;
    g_status = STATUS_OK;
    return true;
}

void remove() {
    rollback();
    g_installed = false;
    g_status = STATUS_NOT_ATTEMPTED;
}

bool installed() { return g_installed; }
InstallStatus last_status() { return g_status; }
const OriginalHooks& originals() { return g_originals; }
}
