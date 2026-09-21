#include "aux_session.h"

namespace aux_session {

bool prepare(Session* session,
             xbox360_usb::DeviceHandle* device,
             uint16_t vid, uint16_t pid,
             void* pcm_buffer0,
             void* pcm_buffer1,
             uint32_t pcm_buffer_size) {
    if (!session || !device || !pcm_buffer0 || !pcm_buffer1 ||
        pcm_buffer_size == 0)
        return false;

    const sony_audio_profiles::Profile* profile =
        sony_audio_profiles::find(vid, pid);
    if (!profile) return false;

    Session s = {};
    s.device = device;
    s.vid = vid;
    s.pid = pid;
    s.profile = profile;
    dualsense_channel_router::initialize(&s.dualsense_router);

    if (!audio_device_probe::inspect(
            device, audio_device_probe::TARGET_CONTROLLER_AUX, &s.probe))
        return false;

    if (!s.probe.playback ||
        s.probe.playback_interface != profile->playback.interface_number ||
        s.probe.playback_alternate_setting != profile->playback.alternate_setting ||
        s.probe.playback_interval != profile->playback.interval ||
        !sony_audio_profiles::validate_playback(
            *profile, s.probe.playback_endpoint,
            s.probe.playback_max_packet_size))
        return false;

    xbox360_iso::StreamConfig cfg = {};
    cfg.endpoint_address = s.probe.playback_endpoint;
    cfg.max_packet_size = s.probe.playback_max_packet_size;
    cfg.interval = s.probe.playback_interval;
    cfg.direction = xbox360_iso::STREAM_PLAYBACK;

    if (!xbox360_iso::open(&s.playback, device, cfg))
        return false;

    if (!pcm_transfer::initialize(&s.playback_engine, &s.playback,
                                  pcm_buffer0, pcm_buffer1, pcm_buffer_size)) {
        xbox360_iso::close(&s.playback);
        return false;
    }

    s.ready = true;
    *session = s;
    return true;
}

bool set_dualsense_route(Session* session,
                         dualsense_channel_router::RouteMode mode) {
    if (!session || !session->ready || session->pid != 0x0CE6)
        return false;
    dualsense_channel_router::set_mode(&session->dualsense_router, mode);
    return true;
}

bool submit_stereo_s16(Session* session,
                       const int16_t* stereo,
                       uint32_t frames,
                       int16_t* conversion_buffer,
                       uint32_t conversion_frames) {
    if (!session || !session->ready || !stereo || frames == 0)
        return false;

    if (session->pid == 0x0CE6) {
        if (!conversion_buffer || conversion_frames < frames)
            return false;
        if (!dualsense_channel_router::stereo_s16_to_4ch(
                &session->dualsense_router, stereo, frames,
                conversion_buffer, conversion_frames))
            return false;
        return pcm_transfer::queue(&session->playback_engine,
                                   conversion_buffer,
                                   frames * 4 * sizeof(int16_t));
    }

    return pcm_transfer::queue(&session->playback_engine,
                               stereo, frames * 2 * sizeof(int16_t));
}

void shutdown(Session* session) {
    if (!session) return;
    pcm_transfer::stop(&session->playback_engine);
    if (session->playback.open)
        xbox360_iso::close(&session->playback);
    session->ready = false;
    session->device = 0;
    session->profile = 0;
}

}
