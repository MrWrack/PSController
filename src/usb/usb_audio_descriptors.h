#pragma once
#include <stdint.h>
#include <stddef.h>

namespace usb_audio {

enum AudioClassCode {
    USB_CLASS_AUDIO = 0x01
};

enum AudioSubclassCode {
    AUDIO_SUBCLASS_CONTROL = 0x01,
    AUDIO_SUBCLASS_STREAMING = 0x02
};

enum EndpointDirection {
    ENDPOINT_OUT = 0,
    ENDPOINT_IN = 1
};

struct InterfaceInfo {
    uint8_t number;
    uint8_t alternate_setting;
    uint8_t interface_class;
    uint8_t interface_subclass;
    uint8_t endpoint_count;
};

struct EndpointInfo {
    uint8_t address;
    uint8_t attributes;
    uint16_t max_packet_size;
    uint8_t interval;
};

struct AudioLayout {
    bool has_control;
    bool has_playback;
    bool has_capture;
    uint8_t control_interface;
    uint8_t playback_interface;
    uint8_t capture_interface;
    uint8_t playback_endpoint;
    uint8_t capture_endpoint;
};

bool is_audio_interface(const InterfaceInfo& info);
bool is_isochronous_endpoint(const EndpointInfo& endpoint);
EndpointDirection endpoint_direction(const EndpointInfo& endpoint);

// Descriptor-first discovery. Callers feed verified interface/endpoint
// descriptors here; this module never assumes fixed endpoint numbers.
bool discover_layout(const InterfaceInfo* interfaces,
                     size_t interface_count,
                     const EndpointInfo* endpoints,
                     size_t endpoint_count,
                     AudioLayout* out_layout);

}
