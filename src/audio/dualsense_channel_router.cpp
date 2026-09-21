#include "dualsense_channel_router.h"

namespace dualsense_channel_router {

void initialize(Router* router) {
    if (router) router->mode = ROUTE_SILENT;
}

void set_mode(Router* router, RouteMode mode) {
    if (router) router->mode = mode;
}

bool stereo_s16_to_4ch(const Router* router,
                       const int16_t* stereo,
                       size_t stereo_frames,
                       int16_t* out4,
                       size_t out4_frames) {
    if (!router || !stereo || !out4 || out4_frames < stereo_frames)
        return false;

    for (size_t i = 0; i < stereo_frames; ++i) {
        const int16_t left = stereo[i * 2];
        const int16_t right = stereo[i * 2 + 1];

        int16_t* frame = &out4[i * 4];
        frame[0] = 0;
        frame[1] = 0;
        frame[2] = 0;
        frame[3] = 0;

        if (router->mode == ROUTE_PAIR_01) {
            frame[0] = left;
            frame[1] = right;
        } else if (router->mode == ROUTE_PAIR_23) {
            frame[2] = left;
            frame[3] = right;
        }
    }

    return true;
}

}
