#pragma once

namespace audio {

enum AuxController {
    AUX_UNKNOWN = 0,
    AUX_DS4,
    AUX_DUALSENSE
};

// Optional subsystem: failure must never make controller input unusable.
bool initialize_optional();
void shutdown();
bool is_available();

bool enable_controller_aux(AuxController controller);
void disable_controller_aux();
bool controller_aux_available();
bool inzone_available();

}
