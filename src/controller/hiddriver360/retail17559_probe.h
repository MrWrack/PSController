#pragma once
#include <stdint.h>

namespace retail17559_probe {

static const uintptr_t HID_ADD_TARGET = 0x800E4D68u;
static const uintptr_t HID_REMOVE_TARGET = 0x800E4D28u;
static const uint32_t MAX_BYTES = 32;

typedef bool (*ReadMemoryFn)(uintptr_t address, void* output, uint32_t length);

struct TargetBytes {
    uintptr_t address;
    uint8_t bytes[MAX_BYTES];
    uint32_t length;
    bool valid;
};

struct Snapshot {
    TargetBytes hid_add;
    TargetBytes hid_remove;
};

// Read-only diagnostic helper. It never writes target memory and never installs
// a detour. Intended to collect bytes from a known 17559 console before a
// verified signature is configured.
bool capture(ReadMemoryFn read_memory, uint32_t length, Snapshot* out);

}
