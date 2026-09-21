#include "test_build_status.h"
#include "hook_diagnostics.h"
#include <string.h>

namespace test_build_status {

void capture(Report* out) {
    if (!out) return;
    memset(out, 0, sizeof(*out));
    out->version = 1;
    out->startup = startup_diagnostics::snapshot();
    out->hook_status_name =
        hook_diagnostics::status_name(out->startup.hook_status);
    hook_diagnostics::describe(
        out->startup.hook_status,
        out->hook_message,
        sizeof(out->hook_message));
}

}
