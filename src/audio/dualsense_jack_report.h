#pragma once
#include <stdint.h>
#include "../usb/xbox360_usb_bridge.h"

namespace dualsense_jack_report {

// DualSense USB main input report: report ID 0x01, 64 bytes.
// Linux hid-playstation defines a 63-byte common payload after the report ID.
// In that payload status[0] is byte 52 and status[1] is byte 53, making
// status[1] absolute USB report byte 54.
static const uint8_t USB_REPORT_ID = 0x01;
static const uint32_t USB_REPORT_SIZE = 64;
static const uint32_t USB_STATUS1_OFFSET = 54;

// Linux hid-playstation DS_STATUS1_* masks.
// These are presence bits: set means the corresponding jack endpoint is
// detected. They are NOT active-low.
static const uint8_t STATUS1_HEADPHONE_DETECT = 1u << 0;
static const uint8_t STATUS1_MIC_DETECT = 1u << 1;
static const uint8_t STATUS1_JACK_DETECT =
    STATUS1_HEADPHONE_DETECT | STATUS1_MIC_DETECT;

bool parse_and_route(xbox360_usb::DeviceHandle* handle,
                     const uint8_t* report,
                     uint32_t length);

}
