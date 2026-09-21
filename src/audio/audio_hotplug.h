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
    DEVICE_INZONE_H9,
    DEVICE_LOGITECH_G733
};

struct Device {
    xbox360_usb::DeviceHandle* handle;
    uint16_t vid;
    uint16_t pid;
    DeviceKind kind;
    bool aux_inserted;
};

void reset();
void on_device_added(const Device& device);
void on_device_removed(xbox360_usb::DeviceHandle* handle);
void set_aux_inserted(xbox360_usb::DeviceHandle* handle, bool inserted);

bool wireless_usb_headset_connected();
bool inzone_connected();
bool logitech_g733_connected();
bool controller_connected();
bool controller_aux_connected();

}
