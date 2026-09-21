#include "xam_voice_probe.h"

namespace {
xam_voice_probe::Api g_api = {};
}

namespace xam_voice_probe {

void set_api(const Api& api) { g_api = api; }

bool api_ready() {
    return g_api.voice_create && g_api.voice_close && g_api.headset_present;
}

Snapshot sample(uint32_t create_arg0, uint32_t create_arg1) {
    Snapshot s = {};
    s.api_ready = api_ready();
    if (!s.api_ready) return s;

    uint32_t voice = 0;
    s.create_result = g_api.voice_create(create_arg0, create_arg1, &voice);
    s.voice_handle = voice;
    s.voice_created = (voice != 0);

    if (s.voice_created) {
        s.headset_result = g_api.headset_present((void*)(uintptr_t)voice);
        s.headset_present = (s.headset_result != 0);
        g_api.voice_close((void*)(uintptr_t)voice);
    }
    return s;
}

}
