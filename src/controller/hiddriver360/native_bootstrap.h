#pragma once
#include "xex_native_entry.h"

namespace native_bootstrap {

// Keeps platform binding and PSController startup/shutdown in one place so the
// eventual DllMain contains no controller/audio policy.
bool start(const xex_native_entry::Services& services);
void stop();
bool running();

}
