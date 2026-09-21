#include "inzone_audio.h"

namespace inzone_audio {

Model identify(const UsbIdentity& id) {
    // Add only VID/PID pairs verified from a real H7/H9 transceiver dump.
    (void)id;
    return MODEL_UNKNOWN;
}

bool probe_device(xbox360_usb::DeviceHandle* device,
                  const UsbIdentity& id,
                  ProbeResult* result) {
    if (!device || !result) return false;

    ProbeResult r = {};
    r.model = identify(id);

    audio_device_probe::Result usb = {};
    if (!audio_device_probe::inspect(
            device, audio_device_probe::TARGET_INZONE, &usb)) {
        *result = r;
        return false;
    }

    r.audio_detected = usb.recognized_audio_layout;
    r.playback = usb.playback;
    r.microphone = usb.microphone;
    r.playback_endpoint = usb.playback_endpoint;
    r.microphone_endpoint = usb.microphone_endpoint;
    *result = r;

    // Descriptor discovery may succeed before identity is verified.
    // Do not bind/stream as INZONE until both conditions are true.
    return r.model != MODEL_UNKNOWN && r.audio_detected;
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
    // Device-specific initialization happens when a verified dongle is attached.
    // Keep startup non-fatal so controller support cannot be blocked by audio.
    return false;
}

void shutdown() {}

}
