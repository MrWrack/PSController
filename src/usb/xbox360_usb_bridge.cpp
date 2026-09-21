#include "xbox360_usb_bridge.h"

namespace {
    xbox360_usb::Api g_api = {};
}

namespace xbox360_usb {

void set_api(const Api& api) { g_api = api; }

bool api_ready() {
    return g_api.get_interface_descriptor != 0 &&
           g_api.get_endpoint_descriptor != 0;
}

bool probe_audio(DeviceHandle* device, usb_audio::AudioLayout* out_layout) {
    if (!device || !out_layout || !api_ready()) return false;

    NativeInterfaceDescriptor* nativeInterface =
        g_api.get_interface_descriptor(device);
    if (!nativeInterface) return false;

    usb_audio::InterfaceInfo interfaceInfo = {};
    interfaceInfo.number = nativeInterface->bInterfaceNumber;
    interfaceInfo.alternate_setting = nativeInterface->bAlternateSetting;
    interfaceInfo.interface_class = nativeInterface->bInterfaceClass;
    interfaceInfo.interface_subclass = nativeInterface->bInterfaceSubClass;
    interfaceInfo.endpoint_count = nativeInterface->bNumEndpoints;

    // HidDriver360 exposes endpoint lookup by transfer type/direction.
    // Probe ISO OUT/IN only. This stage does not open or queue transfers.
    const int ISOCHRONOUS = 1;
    const int OUT = 0;
    const int IN = 1;

    usb_audio::EndpointInfo endpoints[2] = {};
    size_t endpointCount = 0;

    NativeEndpointDescriptor* epOut =
        g_api.get_endpoint_descriptor(device, 0, ISOCHRONOUS, OUT);
    if (epOut) {
        endpoints[endpointCount].address = epOut->bEndpointAddress;
        endpoints[endpointCount].attributes = epOut->bmAttributes;
        endpoints[endpointCount].max_packet_size = epOut->wMaxPacketSize;
        endpoints[endpointCount].interval = epOut->bInterval;
        ++endpointCount;
    }

    NativeEndpointDescriptor* epIn =
        g_api.get_endpoint_descriptor(device, 0, ISOCHRONOUS, IN);
    if (epIn) {
        endpoints[endpointCount].address = epIn->bEndpointAddress;
        endpoints[endpointCount].attributes = epIn->bmAttributes;
        endpoints[endpointCount].max_packet_size = epIn->wMaxPacketSize;
        endpoints[endpointCount].interval = epIn->bInterval;
        ++endpointCount;
    }

    if (endpointCount == 0) return false;

    return usb_audio::discover_layout(
        &interfaceInfo, 1, endpoints, endpointCount, out_layout);
}

}
