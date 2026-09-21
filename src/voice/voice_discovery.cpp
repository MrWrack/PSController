#include "voice_discovery.h"

namespace {
voice_discovery::Resolver g_resolver = {};
static const uint32_t kMicDeviceRequestOrdinal = 0x2B1;
}

namespace voice_discovery {

void set_resolver(const Resolver& resolver) {
    g_resolver = resolver;
}

Result inspect() {
    Result r = {};
    r.mic_device_request_ordinal = kMicDeviceRequestOrdinal;

    if (!g_resolver.get_module_handle ||
        !g_resolver.get_procedure_address)
        return r;

    void* xam = 0;
    if (g_resolver.get_module_handle("xam.xex", &xam) != 0 || !xam)
        return r;
    r.xam_loaded = true;

    void* proc = 0;
    if (g_resolver.get_procedure_address(
            xam, kMicDeviceRequestOrdinal, &proc) != 0 || !proc)
        return r;

    if (g_resolver.is_address_valid &&
        !g_resolver.is_address_valid((uintptr_t)proc))
        return r;

    r.mic_device_request = proc;
    r.mic_device_request_resolved = true;
    return r;
}

}
