#pragma once
#include <stdint.h>

namespace xex_native_entry {

// XEX-facing services are injected so this repository does not ship proprietary
// SDK libraries or guess undocumented loader/detour ABIs.
struct Services {
    unsigned short (*kernel_build)();
    void* (*get_module)(const char* name);
    int (*get_proc)(void* module, uint32_t ordinal, void** out);
    bool (*read_memory)(uintptr_t address, void* out, size_t length);
    bool (*install_detour)(uintptr_t target, void* hook, void** original);
    void (*remove_detour)(uintptr_t target);

    void* hid_add_hook;
    void* hid_remove_hook;
    void* xinput_read_hook;
    void* xam_caps_hook;
    void* xam_set_state_hook;
};

// Binds the native services into the guarded retail-17559 startup path.
// This does not itself initialize PSController.
bool bind(const Services& services);
void unbind();

}
