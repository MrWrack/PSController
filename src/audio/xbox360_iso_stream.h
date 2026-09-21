#pragma once
#include <stdint.h>
#include <stddef.h>
#include "../usb/xbox360_usb_bridge.h"

namespace xbox360_iso {

enum Direction { STREAM_PLAYBACK = 0, STREAM_CAPTURE = 1 };

struct StreamConfig {
    uint8_t endpoint_address;
    uint16_t max_packet_size;
    uint8_t interval;
    Direction direction;
};

// Matches the transfer-request fields used by the verified HidDriver360 USB
// path. Keeping the TRB alive with the stream is required for async transfers.
struct UsbTrb {
    uint32_t endpoint;
    uint32_t callback;
    uint32_t saved_endpoint;
    uint8_t padding[4];
    uint8_t flags;
    uint8_t controller_index;
    uint8_t pad2;
    uint8_t endpoint_index;
    void* buffer;
    uint32_t length;
};

struct Stream {
    xbox360_usb::DeviceHandle* device;
    UsbTrb trb;
    StreamConfig config;
    bool open;
    bool running;
};

struct Api {
    int (*open_endpoint)(xbox360_usb::DeviceHandle*, int transfer_type,
                         int endpoint_address, int max_packet_length,
                         int interval, uint32_t* endpoint);
    int (*close_endpoint)(xbox360_usb::DeviceHandle*, void* endpoint);
    int (*queue_async_transfer)(xbox360_usb::DeviceHandle*, void* trb);
};

void set_api(const Api& api);
bool api_ready();
bool transfer_api_ready();

bool open(Stream* stream, xbox360_usb::DeviceHandle* device,
          const StreamConfig& config);
bool prepare_transfer(Stream* stream, void* buffer, uint32_t length,
                      uint32_t native_callback);
bool queue_prepared(Stream* stream);
void close(Stream* stream);

}
