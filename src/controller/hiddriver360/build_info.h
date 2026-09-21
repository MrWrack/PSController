#pragma once
#include <stdint.h>

namespace build_info {

static const uint32_t TARGET_KERNEL = 17559u;
static const char* const PROJECT_NAME = "PSController";
static const char* const FIRST_TEST_MODE = "diagnostic-only";

struct Info {
    const char* project;
    uint32_t target_kernel;
    const char* mode;
    bool hooks_enabled;
    bool audio_enabled;
};

Info first_test();

}
