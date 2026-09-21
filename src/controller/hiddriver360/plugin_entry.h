#pragma once
#include "native_bootstrap.h"

namespace plugin_entry {

// Keeps DllMain thin. The XDK-facing translation unit supplies Services only
// after every required native function/hook has been verified.
bool process_attach(const xex_native_entry::Services& services);
void process_detach();
bool attached();

}
