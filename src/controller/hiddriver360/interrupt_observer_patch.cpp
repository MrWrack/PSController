#include "interrupt_observer_patch.h"

namespace interrupt_observer_patch {

bool before_mapping(
    const upstream_controller_adapter::UpstreamControllerView* controllers,
    uint32_t controller_count,
    void* driver_extension) {
    if (!controllers || !driver_extension) return false;
    return upstream_controller_adapter::before_input_mapping(
        controllers, controller_count, driver_extension);
}

void before_cleanup(
    const upstream_controller_adapter::UpstreamControllerView* controllers,
    uint32_t controller_count,
    void* device_handle) {
    if (!controllers || !device_handle) return;
    upstream_controller_adapter::before_controller_cleanup(
        controllers, controller_count, device_handle);
}

}
