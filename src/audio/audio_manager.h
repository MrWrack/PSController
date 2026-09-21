#pragma once

namespace audio {
    // Optional subsystem: failure must never make controller input unusable.
    bool initialize_optional();
    void shutdown();
    bool is_available();
}
