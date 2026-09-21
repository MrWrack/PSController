#pragma once
#include <stdint.h>

namespace voice_diag {

enum Phase {
    PHASE_NO_HEADSET = 0,
    PHASE_XBOX_HEADSET,
    PHASE_PLAYSTATION_AUX
};

struct Sample {
    Phase phase;
    bool xam_loaded;
    bool mic_request_resolved;
    bool voice_api_ready;
    bool voice_created;
    bool headset_present;
    uint32_t headset_result;
};

struct Comparison {
    bool baseline_valid;
    bool xbox_headset_changed_state;
    bool playstation_aux_matches_xbox_state;
};

void reset();
void record(const Sample& sample);
Comparison compare();
const Sample* get(Phase phase);

}
