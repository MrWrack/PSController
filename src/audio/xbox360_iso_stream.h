#pragma once
#include <stdint.h>
#include <stddef.h>
#include "../usb/xbox360_usb_bridge.h"

namespace xbox360_iso {

enum Direction {
    STREAM_PLAYBACK = 0,
    STREAM_CAPTURE = 1
};

struct StreamConfig {
    uint8_t endpoint_address;
    uint16_t max_packet_size;
    uint8_t interval;
    Direction direction;
};

struct Stream {
    xbox360_usb::DeviceHandle* device;
    uint32_t endpoint_handle;
    StreamConfig config;
    bool open;
    bool running;
};

struct Api {
    // Mirrors the HidDriver360 UsbdOpenEndpoint / UsbdQueueCloseEndpoint pattern.
    int (*open_endpoint)(xbox360_usb::DeviceHandle*, int transfer_type,
                         int endpoint_address, int max_packet_length,
                         int interval, uint32_t* endpoint);
    int (*close_endpoint)(xbox360_usb::DeviceHandle*, void* endpoint);
};

void set_api(const Api& api);
bool api_ready();

bool open(Stream* stream, xbox360_usb::DeviceHandle* device,
          const StreamConfig& config);
void close(Stream* stream);

}
