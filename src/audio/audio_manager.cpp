#include "audio_manager.h"
#include "dualsense_audio.h"

namespace {
    bool g_audio_available = false;
}

namespace audio {

bool initialize_optional() {
    g_audio_available = dualsense_audio::initialize();
    return g_audio_available;
}

void shutdown() {
    if (g_audio_available) {
        dualsense_audio::shutdown();
        g_audio_available = false;
    }
}

bool is_available() {
    return g_audio_available;
}

}
