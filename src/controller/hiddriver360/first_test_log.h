#pragma once
#include <stdint.h>
#include "first_test_entry.h"

namespace first_test_log {

enum Stage {
    STAGE_IDLE = 0,
    STAGE_STARTING,
    STAGE_DIAGNOSTIC_RUNNING,
    STAGE_DIAGNOSTIC_OK,
    STAGE_RUNTIME_STARTING,
    STAGE_RUNTIME_OK,
    STAGE_FAILED,
    STAGE_STOPPED
};

typedef void (*WriteLineFn)(const char*);

bool start(const boot_mode::Api& api,
           const first_test_entry::Config& config,
           WriteLineFn logger);
void stop(WriteLineFn logger);
Stage stage();
const char* stage_name(Stage stage);

}
