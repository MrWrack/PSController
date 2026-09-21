#pragma once
#include <stdint.h>

namespace voice_format_adapter {

// Conservative chat format used at the platform adapter boundary.
// The final 17559 headset/XHV binding may request a different format;
// keeping conversion isolated makes that change safe.
static const uint32_t CHAT_RATE = 16000;
static const uint8_t CHAT_CHANNELS = 1;

struct Resampler {
    uint32_t phase;
};

void initialize(Resampler* r);

// Converts controller microphone S16 PCM to 16 kHz mono S16.
// Supports DS4 16 kHz mono and DualSense 48 kHz 1/2-channel input.
uint32_t to_chat_mono16(Resampler* r,
                        const int16_t* input,
                        uint32_t input_frames,
                        uint8_t input_channels,
                        uint32_t input_rate,
                        int16_t* output,
                        uint32_t output_capacity);

}
