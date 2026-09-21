#include "pscontroller.h"
#include "audio/audio_manager.h"
#include "controller/hiddriver360/controller_startup.h"

namespace pscontroller {

bool initialize() {
    // Controller input is the primary subsystem. Do not start optional audio
    // unless the verified 17559 controller runtime is alive.
    if (!controller_startup::initialize()) {
        return false;
    }

    // Audio/voice is optional. A failure here must never tear down controller
    // hooks or stop DS4/DualSense input.
    (void)audio::initialize_optional();
    return true;
}

void shutdown() {
    // Stop optional consumers before removing the controller hooks they observe.
    audio::shutdown();
    controller_startup::shutdown();
}

}
