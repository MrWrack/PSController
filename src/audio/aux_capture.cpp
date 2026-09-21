#include "aux_capture.h"

namespace aux_capture {

bool prepare(Session* session,
             xbox360_usb::DeviceHandle* device,
             uint16_t vid, uint16_t pid,
             CaptureCallback callback,
             void* context) {
    if (!session || !device || !callback) return false;

    const sony_audio_profiles::Profile* profile =
        sony_audio_profiles::find(vid, pid);
    if (!profile || profile->capture.endpoint_address == 0 ||
        profile->capture.max_packet_size == 0)
        return false;

    Session s = {};
    s.device = device;
    s.profile = profile;
    s.callback = callback;
    s.callback_context = context;

    xbox360_iso::StreamConfig cfg = {};
    cfg.endpoint_address = profile->capture.endpoint_address;
    cfg.max_packet_size = profile->capture.max_packet_size;
    cfg.interval = profile->capture.interval;
    cfg.direction = xbox360_iso::STREAM_CAPTURE;

    if (!xbox360_iso::open(&s.stream, device, cfg))
        return false;

    s.ready = true;
    *session = s;
    return true;
}

void deliver(Session* session, const void* pcm, uint32_t bytes) {
    if (!session || !session->ready || !session->profile ||
        !session->callback || !pcm)
        return;

    const sony_audio_profiles::StreamProfile& p =
        session->profile->capture;
    const uint32_t bytes_per_frame =
        (uint32_t)p.channels * ((uint32_t)p.bits_per_sample / 8);
    if (bytes_per_frame == 0 || bytes < bytes_per_frame)
        return;

    session->callback((const int16_t*)pcm,
                      bytes / bytes_per_frame,
                      p.channels,
                      p.sample_rate,
                      session->callback_context);
}

void shutdown(Session* session) {
    if (!session) return;
    if (session->stream.open)
        xbox360_iso::close(&session->stream);
    session->ready = false;
    session->device = 0;
    session->profile = 0;
    session->callback = 0;
    session->callback_context = 0;
}

}
