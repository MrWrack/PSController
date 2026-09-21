#pragma once
#include <stdint.h>
#include "../usb/xbox360_usb_bridge.h"

namespace hiddriver_audio_bridge {

// Call from hiddriver360 interruptHandler after locating a valid controller
// slot, before/alongside normal mapping. This function is observational only.
void on_input_report(xbox360_usb::DeviceHandle* handle,
                     uint16_t vid,
                     uint16_t pid,
                     const void* report_buffer,
                     uint32_t report_length);

// Call before the controller slot/driver memory is cleared.
void on_device_removed(xbox360_usb::DeviceHandle* handle);

}
