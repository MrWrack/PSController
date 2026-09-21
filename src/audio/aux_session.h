#pragma once
#include <stdint.h>
#include "audio_device_probe.h"
#include "xbox360_iso_stream.h"
#include "pcm_transfer.h"
#include "sony_audio_profiles.h"
#include "dualsense_channel_router.h"

namespace aux_session {

struct Session {
    xbox360_usb::DeviceHandle* device;
    xbox360_iso::Stream playback;
    pcm_transfer::Engine playback_engine;
    audio_device_probe::Result probe;
    const sony_audio_profiles::Profile* profile;
    dualsense_channel_router::Router dualsense_router;
    uint16_t vid;
    uint16_t pid;
    bool ready;
};

bool prepare(Session* session,
             xbox360_usb::DeviceHandle* device,
             uint16_t vid, uint16_t pid,
             void* pcm_buffer0,
             void* pcm_buffer1,
             uint32_t pcm_buffer_size);

bool set_dualsense_route(Session* session,
                         dualsense_channel_router::RouteMode mode);

bool submit_stereo_s16(Session* session,
                       const int16_t* stereo,
                       uint32_t frames,
                       int16_t* conversion_buffer,
                       uint32_t conversion_frames);

void shutdown(Session* session);

}
