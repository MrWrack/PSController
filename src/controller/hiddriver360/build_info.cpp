#include "build_info.h"

namespace build_info {

Info first_test() {
    Info i = {};
    i.project = PROJECT_NAME;
    i.target_kernel = TARGET_KERNEL;
    i.mode = FIRST_TEST_MODE;
    i.hooks_enabled = false;
    i.audio_enabled = false;
    return i;
}

}
