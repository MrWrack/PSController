#pragma once
#include "retail17559_hooks.h"
#include "controller_startup.h"

namespace startup_diagnostics {

enum Stage {
    STAGE_IDLE = 0,
    STAGE_PLATFORM_BOUND,
    STAGE_CONTROLLER_STARTING,
    STAGE_CONTROLLER_READY,
    STAGE_AUDIO_STARTING,
    STAGE_READY,
    STAGE_FAILED
};

struct Snapshot {
    Stage stage;
    controller_runtime::InitResult controller_result;
    retail17559_hooks::InstallStatus hook_status;
    bool controller_active;
    bool audio_attempted;
};

void reset();
void set_stage(Stage stage);
void set_audio_attempted(bool attempted);
Snapshot snapshot();

}
