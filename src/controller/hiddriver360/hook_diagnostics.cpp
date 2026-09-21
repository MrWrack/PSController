#include "hook_diagnostics.h"
#include <string.h>

namespace hook_diagnostics {

const char* status_name(retail17559_hooks::InstallStatus s) {
    switch (s) {
    case retail17559_hooks::STATUS_NOT_ATTEMPTED: return "not_attempted";
    case retail17559_hooks::STATUS_OK: return "ok";
    case retail17559_hooks::STATUS_ALREADY_INSTALLED: return "already_installed";
    case retail17559_hooks::STATUS_API_MISSING: return "api_missing";
    case retail17559_hooks::STATUS_HOOK_BODY_MISSING: return "hook_body_missing";
    case retail17559_hooks::STATUS_EXPORT_MISSING: return "export_missing";
    case retail17559_hooks::STATUS_SIGNATURE_NOT_CONFIGURED: return "signature_not_configured";
    case retail17559_hooks::STATUS_HID_ADD_SIGNATURE_MISMATCH: return "hid_add_signature_mismatch";
    case retail17559_hooks::STATUS_HID_REMOVE_SIGNATURE_MISMATCH: return "hid_remove_signature_mismatch";
    case retail17559_hooks::STATUS_DETOUR_INSTALL_FAILED: return "detour_install_failed";
    case retail17559_hooks::STATUS_DETOUR_NO_TRAMPOLINE: return "detour_no_trampoline";
    default: return "unknown";
    }
}

bool describe(retail17559_hooks::InstallStatus s,
              char* output,
              unsigned int output_size) {
    if (!output || output_size == 0) return false;
    const char* message = 0;
    switch (s) {
    case retail17559_hooks::STATUS_OK:
        message = "Retail 17559 hooks installed."; break;
    case retail17559_hooks::STATUS_SIGNATURE_NOT_CONFIGURED:
        message = "Blocked: verified retail 17559 HID signatures are not configured."; break;
    case retail17559_hooks::STATUS_HID_ADD_SIGNATURE_MISMATCH:
        message = "Blocked: HID add target does not match the verified 17559 signature."; break;
    case retail17559_hooks::STATUS_HID_REMOVE_SIGNATURE_MISMATCH:
        message = "Blocked: HID remove target does not match the verified 17559 signature."; break;
    case retail17559_hooks::STATUS_DETOUR_INSTALL_FAILED:
        message = "Blocked: native detour installation failed; installed hooks were rolled back."; break;
    case retail17559_hooks::STATUS_DETOUR_NO_TRAMPOLINE:
        message = "Blocked: detour returned no original trampoline; hooks were rolled back."; break;
    case retail17559_hooks::STATUS_EXPORT_MISSING:
        message = "Blocked: required 17559 kernel/XAM export is missing."; break;
    case retail17559_hooks::STATUS_API_MISSING:
        message = "Blocked: native platform hook API is incomplete."; break;
    case retail17559_hooks::STATUS_HOOK_BODY_MISSING:
        message = "Blocked: one or more native hook bodies are missing."; break;
    case retail17559_hooks::STATUS_ALREADY_INSTALLED:
        message = "Retail 17559 hooks were already installed."; break;
    default:
        message = "Retail 17559 hook startup has not completed."; break;
    }
    const size_t n = strlen(message);
    const size_t copy = n < (output_size - 1) ? n : (output_size - 1);
    memcpy(output, message, copy);
    output[copy] = 0;
    return true;
}

}
