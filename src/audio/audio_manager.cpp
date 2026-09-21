#include "audio_manager.h"
#include "dualsense_audio.h"
#include "controller_aux.h"
#include "inzone_audio.h"

namespace {
    bool g_dualsense_audio = false;
    bool g_controller_aux = false;
    bool g_inzone_audio = false;
}

namespace audio {

bool initialize_optional() {
    // Each audio backend is isolated so audio failure never blocks controller input.
    g_dualsense_audio = dualsense_audio::initialize();
    g_controller_aux = false;
    g_inzone_audio = inzone_audio::initialize_optional();
    return is_available();
}

bool enable_controller_aux(AuxController controller) {
    controller_aux::Controller c = controller_aux::CONTROLLER_UNKNOWN;
    if (controller == AUX_DS4) c = controller_aux::CONTROLLER_DS4;
    if (controller == AUX_DUALSENSE) c = controller_aux::CONTROLLER_DUALSENSE;
    g_controller_aux = controller_aux::initialize_optional(c);
    return g_controller_aux;
}

void disable_controller_aux() {
    if (g_controller_aux) controller_aux::shutdown();
    g_controller_aux = false;
}

void shutdown() {
    disable_controller_aux();
    if (g_inzone_audio) inzone_audio::shutdown();
    g_inzone_audio = false;
    if (g_dualsense_audio) dualsense_audio::shutdown();
    g_dualsense_audio = false;
}

bool is_available() {
    return g_dualsense_audio || g_controller_aux || g_inzone_audio;
}

bool controller_aux_available() { return g_controller_aux; }
bool inzone_available() { return g_inzone_audio; }

}
