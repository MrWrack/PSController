#include "retail17559_probe.h"
#include <string.h>

namespace retail17559_probe {

static bool read_target(ReadMemoryFn fn, uintptr_t address,
                        uint32_t length, TargetBytes* out) {
    if (!fn || !out || length == 0 || length > MAX_BYTES) return false;
    memset(out, 0, sizeof(*out));
    out->address = address;
    out->length = length;
    if (!fn(address, out->bytes, length)) return false;
    out->valid = true;
    return true;
}

bool capture(ReadMemoryFn read_memory, uint32_t length, Snapshot* out) {
    if (!out) return false;
    memset(out, 0, sizeof(*out));
    if (!read_memory || length < 4 || length > MAX_BYTES) return false;

    const bool add_ok =
        read_target(read_memory, HID_ADD_TARGET, length, &out->hid_add);
    const bool remove_ok =
        read_target(read_memory, HID_REMOVE_TARGET, length, &out->hid_remove);

    // Partial data remains marked individually for diagnostics.
    return add_ok && remove_ok;
}

}
