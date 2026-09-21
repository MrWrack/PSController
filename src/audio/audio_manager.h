#pragma once

namespace audio {

enum AuxController {
    AUX_UNKNOWN = 0,
    AUX_DS4,
    AUX_DUALSENSE
};

enum OutputRoute {
    OUTPUT_NONE = 0,
    OUTPUT_CONTROLLER_PARTY_ONLY,
    OUTPUT_CONTROLLER_AUX,
    OUTPUT_INZONE
};

// Optional subsystem: failure must never make controller input unusable.
bool initialize_optional();
void shutdown();
bool is_available();

bool enable_controller_aux(AuxController controller);
void disable_controller_aux();

// INZONE H5/H7/H9 has highest priority.
// DualSense/DS4 with AUX inserted gets full routed audio + chat.
// With AUX removed, controller audio is Party Chat only (no game audio).
void set_inzone_present(bool present);
void set_controller_connected(bool present);
void set_controller_aux_present(bool present);
OutputRoute active_output();
bool controller_aux_available();
bool inzone_available();

}
