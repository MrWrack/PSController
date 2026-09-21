#pragma once
#include <stdint.h>
#include "audio_device_probe.h"
#include "xbox360_iso_stream.h"
#include "pcm_transfer.h"

namespace aux_session {

struct Session {
    xbox360_usb::DeviceHandle* device;
    xbox360_iso::Stream playback;
    pcm_transfer::Engine playback_engine;
    audio_device_probe::Result probe;
    bool ready;
};

bool prepare(Session* session,
             xbox360_usb::DeviceHandle* device,
             void* pcm_buffer0,
             void* pcm_buffer1,
             uint32_t pcm_buffer_size);

bool submit_pcm(Session* session, const void* pcm, uint32_t bytes);
void shutdown(Session* session);

}
