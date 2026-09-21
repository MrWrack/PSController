#include "retail17559_hooks.h"
#include <string.h>

namespace retail17559_hooks {
static HookApi g_api = {};
static VerifiedSignatures g_signatures = {};
static OriginalHooks g_originals = {};
static bool g_installed = false;
static uintptr_t g_targets[5] = {0,0,0,0,0};

static const uintptr_t HID_ADD = 0x800E4D68u;
static const uintptr_t HID_REMOVE = 0x800E4D28u;

static bool valid_signature(const TargetSignature& s) {
    return s.bytes && s.length >= 4 && s.length <= 32;
}

static bool match(uintptr_t address, const TargetSignature& signature) {
    if (!g_api.read_memory || !valid_signature(signature)) return false;
    uint8_t actual[32] = {};
    if (!g_api.read_memory(address, actual, signature.length)) return false;
    return memcmp(actual, signature.bytes, signature.length) == 0;
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
        for (int i = 4; i >= 0; --i) {
            if (g_targets[i]) g_api.remove_detour(g_targets[i]);
        }
    }
    clear_runtime_state();
}

bool install(const controller_runtime::ResolvedExports& e,
             void* ha, void* hr, void* xi, void* xc, void* xs) {
    if (g_installed) return true;
    if (!g_api.install_detour || !g_api.read_memory ||
        !ha || !hr || !xi || !xc || !xs) return false;
    if (!e.xinputd_read_state || !e.xam_input_get_capabilities_ex ||
        !e.xam_input_set_state) return false;

    if (!valid_signature(g_signatures.hid_add) ||
        !valid_signature(g_signatures.hid_remove)) return false;
    if (!match(HID_ADD, g_signatures.hid_add) ||
        !match(HID_REMOVE, g_signatures.hid_remove)) return false;

    uintptr_t targets[5] = {
        HID_ADD, HID_REMOVE,
        (uintptr_t)e.xinputd_read_state,
        (uintptr_t)e.xam_input_get_capabilities_ex,
        (uintptr_t)e.xam_input_set_state
    };
    void* hooks[5] = {ha, hr, xi, xc, xs};
    void** originals_out[5] = {
        &g_originals.hid_add, &g_originals.hid_remove,
        &g_originals.xinput_read, &g_originals.xam_caps,
        &g_originals.xam_set_state
    };

    clear_runtime_state();
    for (int i = 0; i < 5; ++i) {
        void* original = 0;
        if (!g_api.install_detour(targets[i], hooks[i], &original) || !original) {
            rollback();
            return false;
        }
        g_targets[i] = targets[i];
        *originals_out[i] = original;
    }

    g_installed = true;
    return true;
}

void remove() {
    rollback();
    g_installed = false;
}

bool installed() { return g_installed; }
const OriginalHooks& originals() { return g_originals; }

}
