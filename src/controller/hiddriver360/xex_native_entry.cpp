#include "xex_native_entry.h"
#include "retail17559_platform.h"

namespace xex_native_entry {

bool bind(const Services& s) {
    retail17559_platform::NativeApi api = {};
    api.kernel_build = s.kernel_build;
    api.get_module = s.get_module;
    api.get_proc = s.get_proc;
    api.read_memory = s.read_memory;
    api.install_detour = s.install_detour;
    api.remove_detour = s.remove_detour;
    api.hid_add_hook = s.hid_add_hook;
    api.hid_remove_hook = s.hid_remove_hook;
    api.xinput_read_hook = s.xinput_read_hook;
    api.xam_caps_hook = s.xam_caps_hook;
    api.xam_set_state_hook = s.xam_set_state_hook;
    return retail17559_platform::bind(api);
}

void unbind() {
    retail17559_platform::unbind();
}

}
