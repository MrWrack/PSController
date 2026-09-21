#include "voice_diag_state.h"

namespace {
voice_diag::Sample g_samples[3] = {};
bool g_valid[3] = { false, false, false };
}

namespace voice_diag {

void reset() {
    for (int i = 0; i < 3; ++i) {
        g_samples[i] = Sample();
        g_valid[i] = false;
    }
}

void record(const Sample& sample) {
    const int i = (int)sample.phase;
    if (i < 0 || i >= 3) return;
    g_samples[i] = sample;
    g_valid[i] = true;
}

const Sample* get(Phase phase) {
    const int i = (int)phase;
    if (i < 0 || i >= 3 || !g_valid[i]) return 0;
    return &g_samples[i];
}

Comparison compare() {
    Comparison c = {};
    if (!g_valid[PHASE_NO_HEADSET]) return c;
    c.baseline_valid = true;

    if (g_valid[PHASE_XBOX_HEADSET]) {
        c.xbox_headset_changed_state =
            g_samples[PHASE_NO_HEADSET].headset_present !=
            g_samples[PHASE_XBOX_HEADSET].headset_present ||
            g_samples[PHASE_NO_HEADSET].headset_result !=
            g_samples[PHASE_XBOX_HEADSET].headset_result;
    }

    if (g_valid[PHASE_XBOX_HEADSET] && g_valid[PHASE_PLAYSTATION_AUX]) {
        c.playstation_aux_matches_xbox_state =
            g_samples[PHASE_XBOX_HEADSET].headset_present ==
            g_samples[PHASE_PLAYSTATION_AUX].headset_present &&
            g_samples[PHASE_XBOX_HEADSET].headset_result ==
            g_samples[PHASE_PLAYSTATION_AUX].headset_result;
    }
    return c;
}

}
