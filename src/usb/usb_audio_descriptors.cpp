#include "usb_audio_descriptors.h"

namespace usb_audio {

bool is_audio_interface(const InterfaceInfo& info) { return info.interface_class == USB_CLASS_AUDIO; }
bool is_isochronous_endpoint(const EndpointInfo& endpoint) { return (endpoint.attributes & 0x03) == 0x01; }
EndpointDirection endpoint_direction(const EndpointInfo& endpoint) {
    return (endpoint.address & 0x80) ? ENDPOINT_IN : ENDPOINT_OUT;
}

static bool is_streaming_interface(const InterfaceInfo* interfaces, size_t count,
                                   uint8_t number, uint8_t alt) {
    for (size_t i = 0; i < count; ++i)
        if (interfaces[i].number == number &&
            interfaces[i].alternate_setting == alt &&
            interfaces[i].interface_class == USB_CLASS_AUDIO &&
            interfaces[i].interface_subclass == AUDIO_SUBCLASS_STREAMING)
            return true;
    return false;
}

bool discover_layout(const InterfaceInfo* interfaces, size_t interface_count,
                     const EndpointInfo* endpoints, size_t endpoint_count,
                     AudioLayout* out_layout) {
    if (!interfaces || !endpoints || !out_layout) return false;
    AudioLayout layout = {};

    for (size_t i = 0; i < interface_count; ++i) {
        const InterfaceInfo& inf = interfaces[i];
        if (inf.interface_class == USB_CLASS_AUDIO &&
            inf.interface_subclass == AUDIO_SUBCLASS_CONTROL) {
            layout.has_control = true;
            layout.control_interface = inf.number;
        }
    }

    for (size_t i = 0; i < endpoint_count; ++i) {
        const EndpointInfo& ep = endpoints[i];
        if (!is_isochronous_endpoint(ep)) continue;
        if (!is_streaming_interface(interfaces, interface_count,
                                    ep.interface_number, ep.alternate_setting))
            continue;

        if (endpoint_direction(ep) == ENDPOINT_OUT && !layout.has_playback) {
            layout.has_playback = true;
            layout.playback_interface = ep.interface_number;
            layout.playback_alternate_setting = ep.alternate_setting;
            layout.playback_endpoint = ep.address;
            layout.playback_max_packet_size = ep.max_packet_size;
            layout.playback_interval = ep.interval;
        } else if (endpoint_direction(ep) == ENDPOINT_IN && !layout.has_capture) {
            layout.has_capture = true;
            layout.capture_interface = ep.interface_number;
            layout.capture_alternate_setting = ep.alternate_setting;
            layout.capture_endpoint = ep.address;
            layout.capture_max_packet_size = ep.max_packet_size;
            layout.capture_interval = ep.interval;
        }
    }

    *out_layout = layout;
    return layout.has_control && (layout.has_playback || layout.has_capture);
}
}
