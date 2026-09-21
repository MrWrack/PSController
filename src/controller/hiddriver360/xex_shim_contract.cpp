#include "xex_shim_contract.h"

namespace xex_shim_contract {
static bool g_attached = false;

bool process_attach(const Platform& p) {
    if (g_attached) return true;
    if (!p.detect_kernel_build || !p.make_boot_api || !p.logger) return false;

    uint32_t build = 0;
    if (!p.detect_kernel_build(&build)) return false;

    boot_mode::Api boot = {};
    if (!p.make_boot_api(&boot)) return false;

    native_test_host::Services services = {};
    services.boot = boot;
    services.logger = p.logger;
    services.kernel_build = build;

    if (native_test_host::attach(services) != native_test_host::HOST_OK)
        return false;

    g_attached = true;
    return true;
}

void process_detach() {
    if (!g_attached) return;
    native_test_host::detach();
    g_attached = false;
}

native_test_host::HostStatus host_status() {
    return native_test_host::status();
}
}
