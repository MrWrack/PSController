#pragma once
#include <stdint.h>

namespace sony_audio_profiles {

enum Model {
    MODEL_UNKNOWN = 0,
    MODEL_DS4_V2,
    MODEL_DUALSENSE
};

struct StreamProfile {
    uint8_t interface_number;
    uint8_t alternate_setting;
    uint8_t endpoint_address;
    uint16_t max_packet_size;
    uint8_t interval;
    uint32_t sample_rate;
    uint8_t channels;
    uint8_t bits_per_sample;
};

struct Profile {
    uint16_t vid;
    uint16_t pid;
    StreamProfile playback;
    StreamProfile capture;
};

const Profile* find(uint16_t vid, uint16_t pid);
bool validate_playback(const Profile& profile,
                       uint8_t endpoint_address,
                       uint16_t max_packet_size);
bool validate_capture(const Profile& profile,
                      uint8_t endpoint_address,
                      uint16_t max_packet_size);

}
