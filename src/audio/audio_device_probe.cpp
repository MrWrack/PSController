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
    r.playback_interface = layout.playback_interface;
    r.playback_alternate_setting = layout.playback_alternate_setting;
    r.playback_endpoint = layout.playback_endpoint;
    r.playback_max_packet_size = layout.playback_max_packet_size;
    r.playback_interval = layout.playback_interval;
    r.microphone_interface = layout.capture_interface;
    r.microphone_alternate_setting = layout.capture_alternate_setting;
    r.microphone_endpoint = layout.capture_endpoint;
    r.microphone_max_packet_size = layout.capture_max_packet_size;
    r.microphone_interval = layout.capture_interval;
    *result = r;
    return r.playback || r.microphone;
}
}
