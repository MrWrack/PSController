#pragma once
#include <stdint.h>

namespace inzone_audio {

enum Model {
    MODEL_UNKNOWN = 0,
    MODEL_H7,
    MODEL_H9
};

struct UsbIdentity {
    uint16_t vid;
    uint16_t pid;
};

struct Capabilities {
    bool game_output;
    bool chat_output;
    bool microphone_input;
    bool game_chat_balance;
    bool headset_volume;
    bool microphone_mute;
};

// Detection is descriptor-first. Do not guess undocumented product IDs.
// VID/PID values observed during Xbox/PC testing can be added later.
Model identify(const UsbIdentity& id);
bool probe_audio_interfaces();
Capabilities expected_capabilities(Model model);
bool initialize_optional();
void shutdown();

}
