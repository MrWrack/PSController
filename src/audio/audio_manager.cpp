#include "audio_manager.h"
#include "dualsense_audio.h"
#include "controller_aux.h"
#include "inzone_audio.h"

namespace {
bool g_dualsense_audio = false;
bool g_controller_aux = false;
bool g_controller_connected = false;
bool g_controller_is_dualsense = false;
bool g_controller_aux_present = false;
bool g_usb_headset_audio = false;
bool g_usb_headset_present = false;
audio::OutputRoute g_route = audio::OUTPUT_NONE;
audio::MicrophoneRoute g_mic = audio::MIC_NONE;

void refresh_routes() {
    if (g_usb_headset_present && g_usb_headset_audio) {
        g_route = audio::OUTPUT_USB_HEADSET;
        g_mic = audio::MIC_USB_HEADSET;
        return;
    }
    if (g_controller_aux_present && g_controller_aux) {
        g_route = audio::OUTPUT_CONTROLLER_AUX;
        g_mic = audio::MIC_CONTROLLER_AUX;
        return;
    }
    if (g_controller_connected && g_controller_is_dualsense && g_dualsense_audio) {
        g_route = audio::OUTPUT_CONTROLLER_CHAT_ONLY;
        g_mic = audio::MIC_DUALSENSE_BUILTIN;
        return;
    }
    g_route = audio::OUTPUT_NONE;
    g_mic = audio::MIC_NONE;
}
}

namespace audio {

bool initialize_optional() {
    g_dualsense_audio = dualsense_audio::initialize();
    g_controller_aux = false;
    g_controller_connected = false;
    g_controller_is_dualsense = false;
    g_controller_aux_present = false;
    g_usb_headset_audio = inzone_audio::initialize_optional();
    g_usb_headset_present = false;
    refresh_routes();
    return is_available();
}

bool enable_controller_aux(AuxController controller) {
    controller_aux::Controller c = controller_aux::CONTROLLER_UNKNOWN;
    if (controller == AUX_DS4) c = controller_aux::CONTROLLER_DS4;
    if (controller == AUX_DUALSENSE) c = controller_aux::CONTROLLER_DUALSENSE;
    g_controller_aux = controller_aux::initialize_optional(c);
    g_controller_connected = controller != AUX_UNKNOWN;
    g_controller_is_dualsense = controller == AUX_DUALSENSE;
    refresh_routes();
    return g_controller_aux;
}

void disable_controller_aux() {
    if (g_controller_aux) controller_aux::shutdown();
    g_controller_aux = false;
    g_controller_aux_present = false;
    refresh_routes();
}

void set_usb_headset_present(bool present) { g_usb_headset_present = present; refresh_routes(); }
void set_inzone_present(bool present) { set_usb_headset_present(present); }

void set_controller_connected(bool present) {
    g_controller_connected = present;
    if (!present) g_controller_is_dualsense = false;
    refresh_routes();
}
void set_controller_aux_present(bool present) { g_controller_aux_present = present; refresh_routes(); }
void set_controller_is_dualsense(bool dualsense) { g_controller_is_dualsense = dualsense; refresh_routes(); }

OutputRoute active_output() { return g_route; }

OutputPolicy active_output_policy() {
    OutputPolicy p = {};
    if (g_route == OUTPUT_USB_HEADSET || g_route == OUTPUT_CONTROLLER_AUX) {
        p.game_audio = true;
        p.party_chat = true;
        p.game_chat = true;
    } else if (g_route == OUTPUT_CONTROLLER_CHAT_ONLY) {
        p.game_audio = false;
        p.party_chat = true;
        p.game_chat = true;
    }
    return p;
}

MicrophoneRoute active_microphone() { return g_mic; }

void shutdown() {
    disable_controller_aux();
    g_controller_connected = false;
    g_controller_is_dualsense = false;
    if (g_usb_headset_audio) inzone_audio::shutdown();
    g_usb_headset_audio = false;
    g_usb_headset_present = false;
    if (g_dualsense_audio) dualsense_audio::shutdown();
    g_dualsense_audio = false;
    refresh_routes();
}

bool is_available() { return g_dualsense_audio || g_controller_aux || g_usb_headset_audio; }
bool controller_aux_available() { return g_controller_aux; }
bool usb_headset_available() { return g_usb_headset_audio; }
bool inzone_available() { return g_usb_headset_audio; }

}
