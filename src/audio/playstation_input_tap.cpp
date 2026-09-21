#include "playstation_input_tap.h"
#include "../controller/playstation_devices.h"
#include "dualsense_jack_report.h"

namespace playstation_input_tap {

void observe(xbox360_usb::DeviceHandle* handle,
             uint16_t vid,
             uint16_t pid,
             const uint8_t* report,
             uint32_t length) {
    if (!handle || !report || length == 0) return;
    if (vid != playstation::SONY_VID) return;

    // Audio is an observer only. Never return a transformed report and never
    // alter controller registration/mapping state here.
    if (pid == playstation::DUALSENSE_PID) {
        (void)dualsense_jack_report::parse_and_route(handle, report, length);
    }

    // DualSense Edge and DS4 are intentionally not routed through the standard
    // DualSense parser until their exact wired jack-state layout is verified.
}

}
