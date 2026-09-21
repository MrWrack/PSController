#pragma once
#include <stdint.h>

namespace party_chat {

enum State {
    STATE_DISABLED = 0,
    STATE_WAITING_FOR_XBOX_VOICE,
    STATE_READY,
    STATE_ERROR
};

struct VoicePcmFormat {
    uint32_t sample_rate;
    uint8_t channels;
    uint8_t bits_per_sample;
};

// Platform adapter. The Xbox 360-specific implementation must bind these
// callbacks to the console's real voice/headset path. Keeping it behind an
// adapter prevents an unverified voice hook from crashing the dashboard.
struct Api {
    bool (*register_virtual_headset)(uint32_t user_index);
    void (*unregister_virtual_headset)(uint32_t user_index);
    bool (*submit_microphone_pcm)(uint32_t user_index,
                                  const int16_t* samples,
                                  uint32_t frames,
                                  const VoicePcmFormat& format);
    uint32_t (*read_chat_pcm)(uint32_t user_index,
                              int16_t* samples,
                              uint32_t max_frames,
                              VoicePcmFormat* format);
};

void set_api(const Api& api);
bool initialize(uint32_t user_index);
void shutdown();
State state();

// AUX capture callback. Feed this directly from aux_capture::deliver().
void on_microphone_pcm(const int16_t* samples,
                       uint32_t frames,
                       uint8_t channels,
                       uint32_t sample_rate,
                       void* context);

// Pull party/chat return audio for routing to the controller AUX output.
uint32_t read_party_audio(int16_t* samples,
                          uint32_t max_frames,
                          VoicePcmFormat* format);

}
