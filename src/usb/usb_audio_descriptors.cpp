#include "usb_audio_descriptors.h"

namespace usb_audio {

bool is_audio_interface(const InterfaceInfo& info) {
    return info.interface_class == USB_CLASS_AUDIO;
}

bool is_isochronous_endpoint(const EndpointInfo& endpoint) {
    return (endpoint.attributes & 0x03) == 0x01;
}

EndpointDirection endpoint_direction(const EndpointInfo& endpoint) {
    return (endpoint.address & 0x80) ? ENDPOINT_IN : ENDPOINT_OUT;
}

bool discover_layout(const InterfaceInfo* interfaces,
                     size_t interface_count,
                     const EndpointInfo* endpoints,
                     size_t endpoint_count,
                     AudioLayout* out_layout) {
    if (!interfaces || !endpoints || !out_layout) return false;

    AudioLayout layout = {};

    for (size_t i = 0; i < interface_count; ++i) {
        const InterfaceInfo& inf = interfaces[i];
        if (!is_audio_interface(inf)) continue;

        if (inf.interface_subclass == AUDIO_SUBCLASS_CONTROL) {
            layout.has_control = true;
            layout.control_interface = inf.number;
        }
    }

    // Endpoint/interface association is completed by the platform USB
    // enumerator. At this generic layer we only accept ISO endpoints and
    // classify their direction; no Sony-specific endpoint number is guessed.
    for (size_t i = 0; i < endpoint_count; ++i) {
        const EndpointInfo& ep = endpoints[i];
        if (!is_isochronous_endpoint(ep)) continue;

        if (endpoint_direction(ep) == ENDPOINT_OUT && !layout.has_playback) {
            layout.has_playback = true;
            layout.playback_endpoint = ep.address;
        } else if (endpoint_direction(ep) == ENDPOINT_IN && !layout.has_capture) {
            layout.has_capture = true;
            layout.capture_endpoint = ep.address;
        }
    }

    *out_layout = layout;
    return layout.has_control && (layout.has_playback || layout.has_capture);
}

}
