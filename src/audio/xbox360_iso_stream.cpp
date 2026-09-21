#include "xbox360_iso_stream.h"

namespace {
    xbox360_iso::Api g_api = {};
}

namespace xbox360_iso {

void set_api(const Api& api) { g_api = api; }

bool api_ready() {
    return g_api.open_endpoint != 0 && g_api.close_endpoint != 0;
}

bool open(Stream* stream, xbox360_usb::DeviceHandle* device,
          const StreamConfig& config) {
    if (!stream || !device || !api_ready()) return false;
    if (config.endpoint_address == 0 || config.max_packet_size == 0) return false;

    Stream candidate = {};
    candidate.device = device;
    candidate.config = config;

    const int ISOCHRONOUS = 1;
    int status = g_api.open_endpoint(
        device,
        ISOCHRONOUS,
        config.endpoint_address,
        config.max_packet_size & 0x7FF,
        config.interval,
        &candidate.endpoint_handle);

    if (status < 0 || candidate.endpoint_handle == 0) return false;

    candidate.open = true;
    candidate.running = false;
    *stream = candidate;
    return true;
}

void close(Stream* stream) {
    if (!stream || !stream->open) return;

    // Streaming/queued transfers are not enabled yet, so close is safe here.
    if (api_ready())
        g_api.close_endpoint(stream->device, (void*)&stream->endpoint_handle);

    stream->endpoint_handle = 0;
    stream->open = false;
    stream->running = false;
    stream->device = 0;
}

}
