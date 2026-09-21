#pragma once
#include <stdint.h>
#include "diagnostic_boot.h"
#include "plugin_entry.h"

namespace boot_mode {

enum Mode {
    MODE_DIAGNOSTIC_ONLY = 0,
    MODE_CONTROLLER_RUNTIME
};

struct Config {
    Mode mode;
    uint32_t probe_bytes;
};

struct Api {
    diagnostic_boot::Api diagnostic;
    xex_native_entry::Services native_services;
};

// Diagnostic mode never starts controller hooks. Runtime mode uses the guarded
// plugin lifecycle and therefore still requires verified signatures.
bool start(const Config& config, const Api& api);
void stop();
Mode active_mode();
bool active();

}
