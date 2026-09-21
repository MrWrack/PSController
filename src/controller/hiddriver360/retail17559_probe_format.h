#pragma once
#include <stdint.h>
#include "retail17559_probe.h"

namespace retail17559_probe_format {

// Produces one compact line per target using caller-owned storage.
// Example shape: "HID_ADD @800E4D68: AA BB CC DD"
// Returns false if the snapshot/target is invalid or output is too small.
bool format_target(const char* name,
                   const retail17559_probe::TargetBytes& target,
                   char* output,
                   uint32_t output_size);

}
