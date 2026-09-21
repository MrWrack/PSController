#include "diagnostic_boot.h"
#include "retail17559_probe_format.h"

namespace diagnostic_boot {
static Result g_last = RESULT_NOT_RUN;

Result run(const Api& api, uint32_t byte_count) {
    g_last = RESULT_NOT_RUN;
    if (!api.read_memory || !api.write_line ||
        byte_count < 4 || byte_count > retail17559_probe::MAX_BYTES) {
        g_last = RESULT_INVALID_API;
        return g_last;
    }

    retail17559_probe::Snapshot s = {};
    if (!retail17559_probe::capture(api.read_memory, byte_count, &s)) {
        g_last = RESULT_CAPTURE_FAILED;
        return g_last;
    }

    char line[160] = {};
    if (retail17559_probe_format::format_target(
            "HID_ADD", s.hid_add, line, sizeof(line)))
        api.write_line(line);

    if (retail17559_probe_format::format_target(
            "HID_REMOVE", s.hid_remove, line, sizeof(line)))
        api.write_line(line);

    g_last = RESULT_OK;
    return g_last;
}

Result last_result() { return g_last; }
}
