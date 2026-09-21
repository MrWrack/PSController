#pragma once
#include <stdint.h>
#include "../usb/xbox360_usb_bridge.h"

namespace playstation_input_tap {

// Non-owning observer for controller input reports.
// The normal controller mapping path must run regardless of this observer's
// result; audio detection is never allowed to consume or block HID input.
void observe(xbox360_usb::DeviceHandle* handle,
             uint16_t vid,
             uint16_t pid,
             const uint8_t* report,
             uint32_t length);

}
