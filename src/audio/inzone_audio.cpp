#include "inzone_audio.h"

namespace inzone_audio {

Model identify(const UsbIdentity& id) {
    // TODO: fill only with VID/PID pairs verified from the user's H7/H9
    // transceiver descriptor dump. Keeping unknown IDs out prevents
    // accidentally binding PSController to unrelated USB devices.
    (void)id;
    return MODEL_UNKNOWN;
}

bool probe_audio_interfaces() {
    // TODO:
    // Enumerate the USB transceiver's interfaces and endpoints.
    // Accept only a descriptor layout verified as an INZONE H7/H9 dongle.
    // Discover playback/chat/microphone paths without assuming endpoint numbers.
    return false;
}

Capabilities expected_capabilities(Model model) {
    Capabilities c = {};
    if (model == MODEL_H7 || model == MODEL_H9) {
        c.game_output = true;
        c.chat_output = true;
        c.microphone_input = true;
        c.game_chat_balance = true;
        c.headset_volume = true;
        c.microphone_mute = true;
    }
    return c;
}

bool initialize_optional() {
    // Failure here must never disable controller input.
    return probe_audio_interfaces();
}

void shutdown() {
    // Safe no-op until USB streams are implemented.
}

}
