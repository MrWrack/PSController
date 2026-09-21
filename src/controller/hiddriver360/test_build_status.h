#pragma once
#include "startup_diagnostics.h"

namespace test_build_status {

// Compact snapshot suitable for debug output on the first retail-17559 build.
struct Report {
    unsigned int version;
    startup_diagnostics::Snapshot startup;
    const char* hook_status_name;
    char hook_message[160];
};

void capture(Report* out);

}
