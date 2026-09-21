#pragma once
#include <stdint.h>
#include "retail17559_probe.h"

namespace diagnostic_boot {

enum Result {
    RESULT_NOT_RUN = 0,
    RESULT_OK,
    RESULT_INVALID_API,
    RESULT_CAPTURE_FAILED
};

struct Api {
    retail17559_probe::ReadMemoryFn read_memory;
    void (*write_line)(const char* line);
};

Result run(const Api& api, uint32_t byte_count);
Result last_result();

}
