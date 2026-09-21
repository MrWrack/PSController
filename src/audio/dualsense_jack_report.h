#pragma once
#include <stdint.h>
#include "../usb/xbox360_usb_bridge.h"

namespace dualsense_jack_report {

// DualSense USB main input report: report ID 0x01, 64 bytes.
// The common payload starts at byte 1. Its status[1] byte is payload offset 53,
// therefore absolute USB report offset 54.
static const uint8_t USB_REPORT_ID = 0x01;
static const uint32_t USB_REPORT_SIZE = 64;
static const uint32_t USB_STATUS1_OFFSET = 54;

// Sony/Linux naming: active-low jack detect bits.
static const uint8_t STATUS1_HEADPHONE_DETECT = 1u << 0;
static const uint8_t STATUS1_MIC_DETECT = 1u << 1;
static const uint8_t STATUS1_JACK_DETECT =
    STATUS1_HEADPHONE_DETECT | STATUS1_MIC_DETECT;

// Returns true only for a structurally valid DualSense USB input report.
// A successful parse forwards the decoded physical jack state to audio hotplug.
bool parse_and_route(xbox360_usb::DeviceHandle* handle,
                     const uint8_t* report,
                     uint32_t length);

}
