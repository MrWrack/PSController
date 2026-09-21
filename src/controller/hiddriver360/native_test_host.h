#pragma once
#include <stdint.h>
#include "first_test_log.h"

namespace native_test_host {

// Platform/build-specific code fills these callbacks. The portable core does
// not import proprietary SDK headers.
struct Services {
    boot_mode::Api boot;
    first_test_log::WriteLineFn logger;
    uint32_t kernel_build;
};

enum HostStatus {
    HOST_NOT_STARTED = 0,
    HOST_OK,
    HOST_UNSUPPORTED_KERNEL,
    HOST_MISSING_LOGGER,
    HOST_START_FAILED
};

HostStatus attach(const Services& services);
void detach();
HostStatus status();

}
