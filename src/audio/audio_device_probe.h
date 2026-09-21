#pragma once
#include "../usb/xbox360_usb_bridge.h"
#include "../usb/usb_audio_descriptors.h"

namespace audio_device_probe {

enum Target {
    TARGET_UNKNOWN = 0,
    TARGET_CONTROLLER_AUX,
    TARGET_INZONE
};

struct Result {
    bool recognized_audio_layout;
    bool playback;
    bool microphone;
    uint8_t playback_endpoint;
    uint8_t microphone_endpoint;
};

bool inspect(xbox360_usb::DeviceHandle* device, Target target, Result* result);

}
