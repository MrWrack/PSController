#include "dualsense_jack_report.h"
#include "sony_aux_detect.h"

namespace dualsense_jack_report {

bool parse_and_route(xbox360_usb::DeviceHandle* handle,
                     const uint8_t* report,
                     uint32_t length) {
    if (!handle || !report) return false;
    if (length != USB_REPORT_SIZE) return false;
    if (report[0] != USB_REPORT_ID) return false;

    const uint8_t raw = report[USB_STATUS1_OFFSET] & STATUS1_JACK_DETECT;

    // DualSense jack-detect signals are active-low in the USB input status:
    // 0 means the corresponding headphone/microphone connection is present.
    sony_aux_detect::JackState state = {};
    state.valid = true;
    state.headphones = (raw & STATUS1_HEADPHONE_DETECT) == 0;
    state.microphone = (raw & STATUS1_MIC_DETECT) == 0;

    sony_aux_detect::on_verified_jack_state(
        handle, sony_aux_detect::CONTROLLER_DUALSENSE, state);
    return true;
}

}
