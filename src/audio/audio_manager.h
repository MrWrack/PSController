#pragma once

namespace audio {

enum AuxController {
    AUX_UNKNOWN = 0,
    AUX_DS4,
    AUX_DUALSENSE
};

enum OutputRoute {
    OUTPUT_NONE = 0,
    OUTPUT_CONTROLLER_AUX,
    OUTPUT_INZONE
};

// Optional subsystem: failure must never make controller input unusable.
bool initialize_optional();
void shutdown();
bool is_available();

bool enable_controller_aux(AuxController controller);
void disable_controller_aux();

// Hot-plug routing: INZONE H5/H7/H9 takes priority while present.
// Removing it falls back to controller AUX when AUX is still available.
void set_inzone_present(bool present);
void set_controller_aux_present(bool present);
OutputRoute active_output();
bool controller_aux_available();
bool inzone_available();

}
