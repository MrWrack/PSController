#pragma once
#include <stdint.h>

namespace controller_aux {

enum Controller {
    CONTROLLER_UNKNOWN = 0,
    CONTROLLER_DS4,
    CONTROLLER_DUALSENSE
};

struct AuxCapabilities {
    bool stereo_output;
    bool microphone_input;
    bool headset_detect;
    bool volume_control;
    bool microphone_mute;
};

// 3.5 mm TRRS headset path exposed through a USB-connected controller.
// This module is independent from USB headset dongles such as INZONE.
bool initialize_optional(Controller controller);
bool probe_headset();
AuxCapabilities capabilities(Controller controller);
void shutdown();

}
