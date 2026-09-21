#include "audio_device_probe.h"

namespace audio_device_probe {

bool inspect(xbox360_usb::DeviceHandle* device, Target target, Result* result) {
    if (!device || !result || target == TARGET_UNKNOWN) return false;

    usb_audio::AudioLayout layout = {};
    if (!xbox360_usb::probe_audio(device, &layout)) return false;

    Result r = {};
    r.recognized_audio_layout = true;
    r.playback = layout.has_playback;
    r.microphone = layout.has_capture;
    r.playback_endpoint = layout.playback_endpoint;
    r.microphone_endpoint = layout.capture_endpoint;
    *result = r;

    return r.playback || r.microphone;
}

}
