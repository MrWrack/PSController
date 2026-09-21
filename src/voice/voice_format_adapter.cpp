#include "voice_format_adapter.h"

namespace voice_format_adapter {

void initialize(Resampler* r) {
    if (r) r->phase = 0;
}

static int16_t mono_sample(const int16_t* input, uint32_t frame,
                           uint8_t channels) {
    if (channels == 1) return input[frame];
    const int32_t a = input[frame * channels];
    const int32_t b = input[frame * channels + 1];
    return (int16_t)((a + b) / 2);
}

uint32_t to_chat_mono16(Resampler* r,
                        const int16_t* input,
                        uint32_t input_frames,
                        uint8_t input_channels,
                        uint32_t input_rate,
                        int16_t* output,
                        uint32_t output_capacity) {
    if (!r || !input || !output || input_frames == 0 ||
        input_channels == 0 || input_rate == 0)
        return 0;

    if (input_rate == CHAT_RATE) {
        uint32_t n = input_frames < output_capacity ?
                     input_frames : output_capacity;
        for (uint32_t i = 0; i < n; ++i)
            output[i] = mono_sample(input, i, input_channels);
        return n;
    }

    // DualSense capture profile is 48 kHz. Exact integer decimation is used
    // here only for voice/chat; a later filter can improve anti-aliasing.
    if (input_rate == 48000) {
        uint32_t out = 0;
        for (uint32_t i = r->phase; i < input_frames && out < output_capacity;
             i += 3)
            output[out++] = mono_sample(input, i, input_channels);
        r->phase = (r->phase + input_frames) % 3;
        return out;
    }

    return 0;
}

}
