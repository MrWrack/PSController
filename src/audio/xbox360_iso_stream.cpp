#include "xbox360_iso_stream.h"

namespace { xbox360_iso::Api g_api = {}; }

namespace xbox360_iso {

void set_api(const Api& api) { g_api = api; }
bool api_ready() { return g_api.open_endpoint != 0 && g_api.close_endpoint != 0; }
bool transfer_api_ready() { return api_ready() && g_api.queue_async_transfer != 0; }

bool open(Stream* stream, xbox360_usb::DeviceHandle* device,
          const StreamConfig& config) {
    if (!stream || !device || !api_ready()) return false;
    if (config.endpoint_address == 0 || config.max_packet_size == 0) return false;

    Stream candidate = {};
    candidate.device = device;
    candidate.config = config;

    const int ISOCHRONOUS = 1;
    int status = g_api.open_endpoint(
        device, ISOCHRONOUS, config.endpoint_address,
        config.max_packet_size & 0x7FF, config.interval,
        &candidate.trb.endpoint);

    if (status < 0 || candidate.trb.endpoint == 0) return false;

    candidate.trb.saved_endpoint = candidate.trb.endpoint;
    candidate.open = true;
    *stream = candidate;
    return true;
}

bool prepare_transfer(Stream* stream, void* buffer, uint32_t length,
                      uint32_t native_callback) {
    if (!stream || !stream->open || !buffer || length == 0) return false;
    if (stream->running) return false;

    stream->trb.buffer = buffer;
    stream->trb.length = length;
    stream->trb.flags = 1;
    stream->trb.callback = native_callback;
    stream->trb.saved_endpoint = stream->trb.endpoint;
    return true;
}

bool queue_prepared(Stream* stream) {
    if (!stream || !stream->open || !transfer_api_ready()) return false;
    if (!stream->trb.buffer || stream->trb.length == 0) return false;

    int status = g_api.queue_async_transfer(stream->device, &stream->trb);
    if (status < 0) return false;
    stream->running = true;
    return true;
}

void close(Stream* stream) {
    if (!stream || !stream->open) return;

    // Do not close a native endpoint while an async request is still owned by
    // the USB stack. The integration layer must complete/cancel it first.
    if (stream->running) return;

    if (api_ready())
        g_api.close_endpoint(stream->device, (void*)&stream->trb);

    stream->trb = UsbTrb();
    stream->open = false;
    stream->device = 0;
}

}
