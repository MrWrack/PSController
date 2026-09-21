#pragma once
#include <stdint.h>
#include <stddef.h>

namespace dualsense_channel_router {

// DualSense exposes a 4-channel, 16-bit playback stream.
// Keep channel placement explicit so hardware testing can verify which
// channels reach the 3.5 mm headset before normal Xbox audio is enabled.
enum RouteMode {
    ROUTE_SILENT = 0,
    ROUTE_PAIR_01,
    ROUTE_PAIR_23
};

struct Router {
    RouteMode mode;
};

void initialize(Router* router);
void set_mode(Router* router, RouteMode mode);

// Converts interleaved stereo S16 PCM into the DualSense 4-channel frame.
// Unselected channels are always zeroed.
bool stereo_s16_to_4ch(const Router* router,
                       const int16_t* stereo,
                       size_t stereo_frames,
                       int16_t* out4,
                       size_t out4_frames);

}
