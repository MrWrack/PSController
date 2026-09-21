#pragma once
#include "retail17559_hooks.h"

namespace hook_diagnostics {

const char* status_name(retail17559_hooks::InstallStatus status);

// Writes a short human-readable explanation into caller storage.
// Returns false only when the output buffer is invalid.
bool describe(retail17559_hooks::InstallStatus status,
              char* output,
              unsigned int output_size);

}
