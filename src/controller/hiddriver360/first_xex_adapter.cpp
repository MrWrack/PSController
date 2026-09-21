#include "first_xex_adapter.h"
#include "retail17559_probe.h"
#include "retail17559_probe_format.h"

namespace first_xex_adapter {

static Status g_status = STATUS_NOT_RUN;

Status process_attach(const Services& services) {
    g_status = STATUS_NOT_RUN;

    if (!services.detect_kernel_build || !services.read_memory || !services.write_line) {
        g_status = STATUS_INVALID_SERVICES;
        return g_status;
    }

    if (services.detect_kernel_build() != 17559u) {
        services.write_line("PSController: unsupported kernel; diagnostic stopped");
        g_status = STATUS_UNSUPPORTED_KERNEL;
        return g_status;
    }

    services.write_line("PSController: first XEX diagnostic adapter");
    services.write_line("PSController: diagnostic-only; hooks/audio disabled");

    retail17559_probe::Snapshot snapshot = {};
    if (!retail17559_probe::capture(services.read_memory, 32u, &snapshot)) {
        services.write_line("PSController: HID probe failed safely");
        g_status = STATUS_PROBE_FAILED;
        return g_status;
    }

    char line[256] = {};
    if (!retail17559_probe_format::format_target("HID_ADD", snapshot.hid_add, line, sizeof(line))) {
        services.write_line("PSController: HID_ADD formatting failed safely");
        g_status = STATUS_PROBE_FAILED;
        return g_status;
    }
    services.write_line(line);

    if (!retail17559_probe_format::format_target("HID_REMOVE", snapshot.hid_remove, line, sizeof(line))) {
        services.write_line("PSController: HID_REMOVE formatting failed safely");
        g_status = STATUS_PROBE_FAILED;
        return g_status;
    }
    services.write_line(line);

    services.write_line("PSController: diagnostic complete; no hooks installed");
    g_status = STATUS_OK;
    return g_status;
}

void process_detach() {
    g_status = STATUS_NOT_RUN;
}

Status status() {
    return g_status;
}

}
