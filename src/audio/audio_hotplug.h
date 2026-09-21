#pragma once
#include <stdint.h>
#include "../usb/xbox360_usb_bridge.h"
#include "inzone_audio.h"

namespace audio_hotplug {

enum DeviceKind {
    DEVICE_OTHER = 0,
    DEVICE_DS4,
    DEVICE_DUALSENSE,
    DEVICE_INZONE_H5,
    DEVICE_INZONE_H7,
    DEVICE_INZONE_H9
};

struct Device {
    xbox360_usb::DeviceHandle* handle;
    uint16_t vid;
    uint16_t pid;
    DeviceKind kind;
};

void reset();

// Called by the USB/HID add/remove bridge. Audio routing is kept separate
// from controller input so an audio failure cannot disconnect the controller.
void on_device_added(const Device& device);
void on_device_removed(xbox360_usb::DeviceHandle* handle);

bool inzone_connected();
bool controller_aux_connected();

}
