#include "sony_aux_detect.h"
#include "audio_hotplug.h"

namespace sony_aux_detect {

void on_verified_jack_state(xbox360_usb::DeviceHandle* handle,
                            ControllerKind controller,
                            const JackState& state) {
    if (!handle || !state.valid) return;
    if (controller != CONTROLLER_DS4 && controller != CONTROLLER_DUALSENSE) return;

    // Treat AUX as inserted when either playback headphones or a headset mic
    // is physically reported. Routing policy decides what audio/mic is active.
    // This never disconnects or reinitializes controller HID input.
    const bool inserted = state.headphones || state.microphone;
    audio_hotplug::set_aux_inserted(handle, inserted);
}

void on_controller_removed(xbox360_usb::DeviceHandle* handle) {
    if (!handle) return;
    audio_hotplug::set_aux_inserted(handle, false);
}

}
