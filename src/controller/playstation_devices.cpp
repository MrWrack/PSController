#include "playstation_devices.h"

namespace playstation {
DeviceType identify(uint16_t vid, uint16_t pid) {
    if (vid != SONY_VID) return DEVICE_UNKNOWN;
    switch (pid) {
        case DS4_V1_PID:
        case DS4_V2_PID:
        case DS4_WIRELESS_ADAPTER_PID:
            return DEVICE_DS4;
        case DUALSENSE_PID:
        case DUALSENSE_EDGE_PID:
            return DEVICE_DUALSENSE;
        default:
            return DEVICE_UNKNOWN;
    }
}

bool supports_usb_input(uint16_t vid, uint16_t pid) {
    return identify(vid, pid) != DEVICE_UNKNOWN;
}

bool may_expose_controller_audio(uint16_t vid, uint16_t pid) {
    // Capability flag only. Actual USB interface/endpoint discovery is required.
    DeviceType type = identify(vid, pid);
    return type == DEVICE_DS4 || type == DEVICE_DUALSENSE;
}
}
