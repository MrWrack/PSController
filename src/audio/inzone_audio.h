#pragma once
#include <stdint.h>
#include "../usb/xbox360_usb_bridge.h"
#include "audio_device_probe.h"

namespace inzone_audio {

enum Model { MODEL_UNKNOWN = 0, MODEL_H5, MODEL_H7, MODEL_H9 };

struct UsbIdentity { uint16_t vid; uint16_t pid; };

struct Capabilities {
    bool game_output;
    bool chat_output;
    bool microphone_input;
    bool game_chat_balance;
    bool headset_volume;
    bool microphone_mute;
};

struct ProbeResult {
    Model model;
    bool audio_detected;
    bool playback;
    bool microphone;
    uint8_t playback_endpoint;
    uint8_t microphone_endpoint;
};

// Detection remains descriptor-first. Unknown dongles are never claimed
// merely because they expose USB Audio.
Model identify(const UsbIdentity& id);
bool probe_device(xbox360_usb::DeviceHandle* device,
                  const UsbIdentity& id,
                  ProbeResult* result);
Capabilities expected_capabilities(Model model);
bool initialize_optional();
void shutdown();

}
