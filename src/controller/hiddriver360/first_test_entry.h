#pragma once
#include <stdint.h>
#include "boot_mode.h"

namespace first_test_entry {

// Build-time-safe default for the first retail-17559 hardware run.
// Runtime hooks cannot be selected accidentally unless the caller explicitly
// opts into MODE_CONTROLLER_RUNTIME.
struct Config {
    boot_mode::Mode mode;
    uint32_t probe_bytes;
};

Config safe_default();
bool start(const boot_mode::Api& api, const Config& config);
void stop();

}
