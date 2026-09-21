#include "native_test_host.h"

namespace native_test_host {
static HostStatus g_status = HOST_NOT_STARTED;
static first_test_log::WriteLineFn g_logger = 0;

HostStatus attach(const Services& s) {
    g_status = HOST_NOT_STARTED;
    g_logger = s.logger;

    if (!g_logger) {
        g_status = HOST_MISSING_LOGGER;
        return g_status;
    }

    if (s.kernel_build != 17559u) {
        g_logger("PSController: unsupported kernel; expected 17559");
        g_status = HOST_UNSUPPORTED_KERNEL;
        return g_status;
    }

    first_test_entry::Config config = first_test_entry::safe_default();
    if (!first_test_log::start(s.boot, config, g_logger)) {
        g_status = HOST_START_FAILED;
        return g_status;
    }

    g_status = HOST_OK;
    return g_status;
}

void detach() {
    if (g_status == HOST_OK)
        first_test_log::stop(g_logger);
    g_logger = 0;
    g_status = HOST_NOT_STARTED;
}

HostStatus status() { return g_status; }
}
