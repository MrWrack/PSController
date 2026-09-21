#pragma once

namespace first_xex_adapter {

typedef unsigned int (*DetectKernelBuildFn)();
typedef bool (*ReadMemoryFn)(unsigned int address, void* out, unsigned int size);
typedef void (*WriteLineFn)(const char* line);

struct Services {
    DetectKernelBuildFn detect_kernel_build;
    ReadMemoryFn read_memory;
    WriteLineFn write_line;
};

enum Status {
    STATUS_NOT_RUN = 0,
    STATUS_OK,
    STATUS_INVALID_SERVICES,
    STATUS_UNSUPPORTED_KERNEL,
    STATUS_PROBE_FAILED
};

Status process_attach(const Services& services);
void process_detach();
Status status();

}
