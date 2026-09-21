#pragma once
#include <stdint.h>
#include "usb_audio_descriptors.h"

// Xbox 360 retail-kernel USB bridge.
// Function shapes are based on the USB access pattern used by HidDriver360.
// The actual kernel ordinals/import resolution are integrated at plugin level.

namespace xbox360_usb {

struct DeviceHandle;

struct NativeInterfaceDescriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;
};

struct NativeEndpointDescriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bEndpointAddress;
    uint8_t bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t bInterval;
};

typedef NativeInterfaceDescriptor* (*GetInterfaceDescriptorFn)(DeviceHandle*);
typedef NativeEndpointDescriptor* (*GetEndpointDescriptorFn)(DeviceHandle*, int, int, int);

struct Api {
    GetInterfaceDescriptorFn get_interface_descriptor;
    GetEndpointDescriptorFn get_endpoint_descriptor;
};

void set_api(const Api& api);
bool api_ready();

// Safe first milestone: inspect descriptors only. No stream is opened here.
bool probe_audio(DeviceHandle* device, usb_audio::AudioLayout* out_layout);

}
