#include "target_shim_template.h"

namespace target_shim_template {

first_xex_adapter::Status attach() {
    first_xex_adapter::Services services = {};
    services.detect_kernel_build = &detect_kernel_build;
    services.read_memory = &safe_read_memory;
    services.write_line = &debug_write_line;
    return first_xex_adapter::process_attach(services);
}

void detach() {
    first_xex_adapter::process_detach();
}

}
