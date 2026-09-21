#include "startup_diagnostics.h"

namespace startup_diagnostics {
static Stage g_stage = STAGE_IDLE;
static bool g_audio_attempted = false;

void reset() {
    g_stage = STAGE_IDLE;
    g_audio_attempted = false;
}

void set_stage(Stage stage) { g_stage = stage; }
void set_audio_attempted(bool attempted) { g_audio_attempted = attempted; }

Snapshot snapshot() {
    Snapshot s = {};
    s.stage = g_stage;
    s.controller_result = controller_startup::last_result();
    s.hook_status = retail17559_hooks::last_status();
    s.controller_active = controller_startup::active();
    s.audio_attempted = g_audio_attempted;
    return s;
}
}
