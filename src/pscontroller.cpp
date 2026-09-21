#include "pscontroller.h"
#include "audio/audio_manager.h"
#include "controller/hiddriver360/controller_startup.h"
#include "controller/hiddriver360/startup_diagnostics.h"

namespace pscontroller {

bool initialize() {
    startup_diagnostics::reset();
    startup_diagnostics::set_stage(startup_diagnostics::STAGE_CONTROLLER_STARTING);

    // Controller input is the primary subsystem. Do not start optional audio
    // unless the verified 17559 controller runtime is alive.
    if (!controller_startup::initialize()) {
        startup_diagnostics::set_stage(startup_diagnostics::STAGE_FAILED);
        return false;
    }

    startup_diagnostics::set_stage(startup_diagnostics::STAGE_CONTROLLER_READY);

    // Audio/voice is optional. A failure here must never tear down controller
    // hooks or stop DS4/DualSense input.
    startup_diagnostics::set_stage(startup_diagnostics::STAGE_AUDIO_STARTING);
    startup_diagnostics::set_audio_attempted(true);
    (void)audio::initialize_optional();

    startup_diagnostics::set_stage(startup_diagnostics::STAGE_READY);
    return true;
}

void shutdown() {
    // Stop optional consumers before removing the controller hooks they observe.
    audio::shutdown();
    controller_startup::shutdown();
    startup_diagnostics::reset();
}

}
