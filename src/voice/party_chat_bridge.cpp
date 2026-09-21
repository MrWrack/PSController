#include "party_chat_bridge.h"

namespace {
party_chat::Api g_api = {};
party_chat::State g_state = party_chat::STATE_DISABLED;
uint32_t g_user_index = 0;
}

namespace party_chat {

void set_api(const Api& api) {
    g_api = api;
}

bool initialize(uint32_t user_index) {
    shutdown();
    g_user_index = user_index;

    if (!g_api.register_virtual_headset ||
        !g_api.unregister_virtual_headset ||
        !g_api.submit_microphone_pcm ||
        !g_api.read_chat_pcm) {
        g_state = STATE_WAITING_FOR_XBOX_VOICE;
        return false;
    }

    if (!g_api.register_virtual_headset(user_index)) {
        g_state = STATE_ERROR;
        return false;
    }

    g_state = STATE_READY;
    return true;
}

void shutdown() {
    if (g_state == STATE_READY && g_api.unregister_virtual_headset)
        g_api.unregister_virtual_headset(g_user_index);
    g_state = STATE_DISABLED;
}

State state() {
    return g_state;
}

void on_microphone_pcm(const int16_t* samples,
                       uint32_t frames,
                       uint8_t channels,
                       uint32_t sample_rate,
                       void*) {
    if (g_state != STATE_READY || !samples || frames == 0)
        return;

    VoicePcmFormat fmt = {};
    fmt.sample_rate = sample_rate;
    fmt.channels = channels;
    fmt.bits_per_sample = 16;

    // If the Xbox voice adapter rejects the controller-native format, drop the
    // packet safely. Resampling/downmix belongs in the platform voice adapter.
    g_api.submit_microphone_pcm(g_user_index, samples, frames, fmt);
}

uint32_t read_party_audio(int16_t* samples,
                          uint32_t max_frames,
                          VoicePcmFormat* format) {
    if (g_state != STATE_READY || !samples || !format || max_frames == 0)
        return 0;
    return g_api.read_chat_pcm(g_user_index, samples, max_frames, format);
}

}
