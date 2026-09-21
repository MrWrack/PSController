#include "hiddriver_audio_bridge.h"
#include "playstation_input_tap.h"
#include "sony_aux_detect.h"

namespace hiddriver_audio_bridge {

void on_input_report(xbox360_usb::DeviceHandle* handle,
                     uint16_t vid,
                     uint16_t pid,
                     const void* report_buffer,
                     uint32_t report_length) {
    if (!handle || !report_buffer || report_length == 0) return;

    playstation_input_tap::observe(
        handle, vid, pid,
        static_cast<const uint8_t*>(report_buffer),
        report_length);
}

void on_device_removed(xbox360_usb::DeviceHandle* handle) {
    if (!handle) return;
    sony_aux_detect::on_controller_removed(handle);
}

}
