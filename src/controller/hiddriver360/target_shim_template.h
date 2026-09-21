#pragma once
#include "first_xex_adapter.h"

namespace target_shim_template {

// These functions are deliberately declarations only. The target-specific
// translation unit must implement them from the selected toolchain's verified
// headers/ABI. Do not guess signatures or ordinals.
unsigned int detect_kernel_build();
bool safe_read_memory(unsigned int address, void* out, unsigned int size);
void debug_write_line(const char* line);

// Portable helper used by the eventual native XEX entry point.
first_xex_adapter::Status attach();
void detach();

}
