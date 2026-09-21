#include "aux_session.h"

namespace aux_session {

bool prepare(Session* session,
             xbox360_usb::DeviceHandle* device,
             void* pcm_buffer0,
             void* pcm_buffer1,
             uint32_t pcm_buffer_size) {
    if (!session || !device || !pcm_buffer0 || !pcm_buffer1 ||
        pcm_buffer_size == 0)
        return false;

    Session s = {};
    s.device = device;

    if (!audio_device_probe::inspect(
            device, audio_device_probe::TARGET_CONTROLLER_AUX, &s.probe))
        return false;

    if (!s.probe.playback || s.probe.playback_endpoint == 0)
        return false;

    // Endpoint packet size/interval must be supplied from the verified native
    // descriptor before this can be opened on hardware. Never guess them.
    // prepare() therefore establishes the validated AUX session only; the
    // platform integration completes StreamConfig once descriptors are captured.
    s.ready = true;
    *session = s;
    return true;
}

bool submit_pcm(Session* session, const void* pcm, uint32_t bytes) {
    if (!session || !session->ready || !session->playback.open)
        return false;
    return pcm_transfer::queue(&session->playback_engine, pcm, bytes);
}

void shutdown(Session* session) {
    if (!session) return;
    pcm_transfer::stop(&session->playback_engine);
    if (session->playback.open)
        xbox360_iso::close(&session->playback);
    session->ready = false;
    session->device = 0;
}

}
