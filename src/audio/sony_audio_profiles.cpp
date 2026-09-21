#include "sony_audio_profiles.h"

namespace sony_audio_profiles {

static const Profile kProfiles[] = {
    // DualShock 4 v2 / CUH-ZCT2 family (054C:09CC)
    {
        0x054C, 0x09CC,
        { 1, 1, 0x01, 132, 4, 32000, 2, 16 },
        { 2, 1, 0x82, 34,  4, 16000, 1, 16 }
    },
    // DualSense / CFI-ZCT1 family (054C:0CE6)
    {
        0x054C, 0x0CE6,
        { 1, 1, 0x01, 392, 4, 48000, 4, 16 },
        { 2, 1, 0x82, 196, 4, 48000, 2, 16 }
    }
};

const Profile* find(uint16_t vid, uint16_t pid) {
    for (unsigned i = 0; i < sizeof(kProfiles) / sizeof(kProfiles[0]); ++i)
        if (kProfiles[i].vid == vid && kProfiles[i].pid == pid)
            return &kProfiles[i];
    return 0;
}

bool validate_playback(const Profile& p, uint8_t ep, uint16_t packet) {
    return p.playback.endpoint_address == ep &&
           p.playback.max_packet_size == packet;
}

bool validate_capture(const Profile& p, uint8_t ep, uint16_t packet) {
    return p.capture.endpoint_address == ep &&
           p.capture.max_packet_size == packet;
}

}
