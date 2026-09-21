#include "controller_aux.h"

namespace controller_aux {

bool initialize_optional(Controller controller) {
    if (controller != CONTROLLER_DS4 && controller != CONTROLLER_DUALSENSE)
        return false;

    // TODO: bind to the verified controller USB audio interfaces.
    // The physical 3.5 mm AUX/TRRS jack is reached through the controller;
    // it is not an analog input on the Xbox 360 itself.
    return probe_headset();
}

bool probe_headset() {
    // TODO: inspect the verified USB audio/control descriptors and detect
    // whether a TRRS headset is attached. Do not guess endpoint numbers.
    return false;
}

AuxCapabilities capabilities(Controller controller) {
    AuxCapabilities c = {};
    if (controller == CONTROLLER_DS4 || controller == CONTROLLER_DUALSENSE) {
        c.stereo_output = true;
        c.microphone_input = true;
        c.headset_detect = true;
        c.volume_control = true;
        c.microphone_mute = true;
    }
    return c;
}

void shutdown() {}

}
