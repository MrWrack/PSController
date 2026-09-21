#include "first_test_log.h"

namespace first_test_log {
static Stage g_stage = STAGE_IDLE;

const char* stage_name(Stage s) {
    switch (s) {
        case STAGE_IDLE: return "idle";
        case STAGE_STARTING: return "starting";
        case STAGE_DIAGNOSTIC_RUNNING: return "diagnostic_running";
        case STAGE_DIAGNOSTIC_OK: return "diagnostic_ok";
        case STAGE_RUNTIME_STARTING: return "runtime_starting";
        case STAGE_RUNTIME_OK: return "runtime_ok";
        case STAGE_FAILED: return "failed";
        case STAGE_STOPPED: return "stopped";
        default: return "unknown";
    }
}

static void log(WriteLineFn fn, const char* text) {
    if (fn) fn(text);
}

bool start(const boot_mode::Api& api,
           const first_test_entry::Config& config,
           WriteLineFn logger) {
    g_stage = STAGE_STARTING;
    log(logger, "PSController: first-test entry starting");

    if (config.mode == boot_mode::MODE_DIAGNOSTIC_ONLY) {
        g_stage = STAGE_DIAGNOSTIC_RUNNING;
        log(logger, "PSController: diagnostic-only mode; hooks/audio disabled");
    } else {
        g_stage = STAGE_RUNTIME_STARTING;
        log(logger, "PSController: guarded controller-runtime requested");
    }

    if (!first_test_entry::start(api, config)) {
        g_stage = STAGE_FAILED;
        log(logger, "PSController: startup failed safely");
        return false;
    }

    if (config.mode == boot_mode::MODE_DIAGNOSTIC_ONLY) {
        g_stage = STAGE_DIAGNOSTIC_OK;
        log(logger, "PSController: diagnostic capture complete; no hooks installed");
    } else {
        g_stage = STAGE_RUNTIME_OK;
        log(logger, "PSController: guarded controller-runtime started");
    }
    return true;
}

void stop(WriteLineFn logger) {
    first_test_entry::stop();
    g_stage = STAGE_STOPPED;
    log(logger, "PSController: stopped");
}

Stage stage() { return g_stage; }
}
