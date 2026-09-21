#pragma once
#include <stdint.h>
#include "../usb/xbox360_usb_bridge.h"

namespace sony_aux_detect {

enum ControllerKind {
    CONTROLLER_UNSUPPORTED = 0,
    CONTROLLER_DS4,
    CONTROLLER_DUALSENSE
};

struct JackState {
    bool valid;
    bool headphones;
    bool microphone;
};

// Feed verified Sony jack state into the audio hot-plug router.
// This module deliberately does not guess HID byte offsets or bit masks.
// The caller must provide state decoded from a verified controller report,
// USB-audio jack event, or hardware-specific Sony parser.
void on_verified_jack_state(xbox360_usb::DeviceHandle* handle,
                            ControllerKind controller,
                            const JackState& state);

// Safe disconnect helper: clears any remembered AUX state without touching HID.
void on_controller_removed(xbox360_usb::DeviceHandle* handle);

}
