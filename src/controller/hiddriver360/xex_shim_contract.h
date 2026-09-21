#pragma once
#include <stdint.h>
#include "native_test_host.h"

namespace xex_shim_contract {

// The actual Xbox/XDK-facing translation unit implements these without leaking
// SDK types into the portable core.
struct Platform {
    bool (*detect_kernel_build)(uint32_t* build);
    bool (*make_boot_api)(boot_mode::Api* out);
    first_test_log::WriteLineFn logger;
};

bool process_attach(const Platform& platform);
void process_detach();
native_test_host::HostStatus host_status();

}
