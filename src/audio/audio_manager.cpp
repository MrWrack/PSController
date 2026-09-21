#include "audio_manager.h"
#include "dualsense_audio.h"
#include "controller_aux.h"
#include "inzone_audio.h"

namespace {
bool g_dualsense_audio = false;
bool g_controller_aux = false;
bool g_controller_aux_present = false;
bool g_inzone_audio = false;
bool g_inzone_present = false;
audio::OutputRoute g_route = audio::OUTPUT_NONE;

void refresh_route() {
    // External USB headset wins over controller AUX.
    if (g_inzone_present && g_inzone_audio) {
        g_route = audio::OUTPUT_INZONE;
        return;
    }
    if (g_controller_aux_present && g_controller_aux) {
        g_route = audio::OUTPUT_CONTROLLER_AUX;
        return;
    }
    g_route = audio::OUTPUT_NONE;
}
}

namespace audio {

bool initialize_optional() {
    g_dualsense_audio = dualsense_audio::initialize();
    g_controller_aux = false;
    g_controller_aux_present = false;
    g_inzone_audio = inzone_audio::initialize_optional();
    g_inzone_present = false;
    refresh_route();
    return is_available();
}

bool enable_controller_aux(AuxController controller) {
    controller_aux::Controller c = controller_aux::CONTROLLER_UNKNOWN;
    if (controller == AUX_DS4) c = controller_aux::CONTROLLER_DS4;
    if (controller == AUX_DUALSENSE) c = controller_aux::CONTROLLER_DUALSENSE;
    g_controller_aux = controller_aux::initialize_optional(c);
    g_controller_aux_present = g_controller_aux;
    refresh_route();
    return g_controller_aux;
}

void disable_controller_aux() {
    if (g_controller_aux) controller_aux::shutdown();
    g_controller_aux = false;
    g_controller_aux_present = false;
    refresh_route();
}

void set_inzone_present(bool present) {
    g_inzone_present = present;
    refresh_route();
}

void set_controller_aux_present(bool present) {
    g_controller_aux_present = present;
    refresh_route();
}

OutputRoute active_output() { return g_route; }

void shutdown() {
    disable_controller_aux();
    if (g_inzone_audio) inzone_audio::shutdown();
    g_inzone_audio = false;
    g_inzone_present = false;
    if (g_dualsense_audio) dualsense_audio::shutdown();
    g_dualsense_audio = false;
    refresh_route();
}

bool is_available() {
    return g_dualsense_audio || g_controller_aux || g_inzone_audio;
}

bool controller_aux_available() { return g_controller_aux; }
bool inzone_available() { return g_inzone_audio; }

}
