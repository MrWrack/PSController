#pragma once
#include <stdint.h>
#include "xbox360_iso_stream.h"
#include "sony_audio_profiles.h"

namespace aux_capture {

typedef void (*CaptureCallback)(const int16_t* samples,
                                uint32_t frames,
                                uint8_t channels,
                                uint32_t sample_rate,
                                void* context);

struct Session {
    xbox360_usb::DeviceHandle* device;
    xbox360_iso::Stream stream;
    const sony_audio_profiles::Profile* profile;
    CaptureCallback callback;
    void* callback_context;
    bool ready;
};

bool prepare(Session* session,
             xbox360_usb::DeviceHandle* device,
             uint16_t vid, uint16_t pid,
             CaptureCallback callback,
             void* context);

// Called by the native USB integration after a completed capture transfer.
void deliver(Session* session, const void* pcm, uint32_t bytes);
void shutdown(Session* session);

}
