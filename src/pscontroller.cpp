#include "pscontroller.h"
#include "audio/audio_manager.h"

namespace pscontroller {

bool initialize() {
    // Controller/HID initialization will be integrated from the GPL-3.0
    // HidDriver360 base. Audio is optional and must fail safely.
    audio::initialize_optional();
    return true;
}

void shutdown() {
    audio::shutdown();
}

}
