#pragma once
#include "../usb/xbox360_usb_bridge.h"
#include "../usb/usb_audio_descriptors.h"

namespace audio_device_probe {
enum Target { TARGET_UNKNOWN = 0, TARGET_CONTROLLER_AUX, TARGET_INZONE };
struct Result {
    bool recognized_audio_layout;
    bool playback;
    bool microphone;
    uint8_t playback_interface;
    uint8_t playback_alternate_setting;
    uint8_t playback_endpoint;
    uint16_t playback_max_packet_size;
    uint8_t playback_interval;
    uint8_t microphone_interface;
    uint8_t microphone_alternate_setting;
    uint8_t microphone_endpoint;
    uint16_t microphone_max_packet_size;
    uint8_t microphone_interval;
};
bool inspect(xbox360_usb::DeviceHandle* device, Target target, Result* result);
}
