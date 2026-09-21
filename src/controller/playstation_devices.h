#pragma once
#include <stdint.h>

namespace playstation {
static const uint16_t SONY_VID = 0x054C;
static const uint16_t DS4_V1_PID = 0x05C4;
static const uint16_t DS4_V2_PID = 0x09CC;
static const uint16_t DS4_WIRELESS_ADAPTER_PID = 0x0BA0;
static const uint16_t DUALSENSE_PID = 0x0CE6;
static const uint16_t DUALSENSE_EDGE_PID = 0x0DF2;

enum DeviceType {
    DEVICE_UNKNOWN = 0,
    DEVICE_DS4,
    DEVICE_DUALSENSE
};

DeviceType identify(uint16_t vid, uint16_t pid);
bool supports_usb_input(uint16_t vid, uint16_t pid);
bool may_expose_controller_audio(uint16_t vid, uint16_t pid);
}
