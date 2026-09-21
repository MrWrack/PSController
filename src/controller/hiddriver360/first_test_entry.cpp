#include "first_test_entry.h"

namespace first_test_entry {

Config safe_default() {
    Config c = {};
    c.mode = boot_mode::MODE_DIAGNOSTIC_ONLY;
    c.probe_bytes = 32;
    return c;
}

bool start(const boot_mode::Api& api, const Config& config) {
    boot_mode::Config c = {};
    c.mode = config.mode;
    c.probe_bytes = config.probe_bytes;

    // Refuse malformed diagnostic settings instead of silently changing mode.
    if (c.mode == boot_mode::MODE_DIAGNOSTIC_ONLY &&
        (c.probe_bytes < 4 ||
         c.probe_bytes > retail17559_probe::MAX_BYTES))
        return false;

    return boot_mode::start(c, api);
}

void stop() { boot_mode::stop(); }

}
