#pragma once
#include <stdint.h>

namespace xam_voice_probe {

// Diagnostic-only adapter for Xbox 360 voice discovery.
// No fixed addresses are used here: platform code must supply verified
// function pointers for the exact 17559 build before calls are enabled.
struct Api {
    uint32_t (*voice_create)(uint32_t a, uint32_t b, uint32_t* out_voice);
    uint32_t (*voice_close)(void* voice);
    uint32_t (*headset_present)(void* voice);
};

struct Snapshot {
    bool api_ready;
    bool voice_created;
    bool headset_present;
    uint32_t create_result;
    uint32_t headset_result;
    uint32_t voice_handle;
};

void set_api(const Api& api);
bool api_ready();

// Read-only diagnostic probe. It never patches code and never forces a
// headset-present result.
Snapshot sample(uint32_t create_arg0, uint32_t create_arg1);

}
