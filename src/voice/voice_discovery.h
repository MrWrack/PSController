#pragma once
#include <stdint.h>

namespace voice_discovery {

struct Resolver {
    int (*get_module_handle)(const char* module_name, void** module);
    int (*get_procedure_address)(void* module, uint32_t ordinal, void** address);
    bool (*is_address_valid)(uintptr_t address);
};

struct Result {
    bool xam_loaded;
    bool mic_device_request_resolved;
    uint32_t mic_device_request_ordinal;
    void* mic_device_request;
};

void set_resolver(const Resolver& resolver);

// Discovery only. Resolves a known public-research lead but never calls it.
Result inspect();

}
