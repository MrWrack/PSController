#include "upstream_controller_adapter.h"

namespace upstream_controller_adapter {

void build_slots(const UpstreamControllerView* source,
                 uint32_t count,
                 native_controller_core::NativeSlot* destination) {
    if (!source || !destination) return;

    for (uint32_t i = 0; i < count; ++i) {
        native_controller_core::NativeSlot slot = {};
        slot.device_handle = source[i].device_handle;
        slot.driver_extension = source[i].controller_driver;
        slot.vendor_id = source[i].vendor_id;
        slot.product_id = source[i].product_id;
        slot.report_buffer = source[i].interrupt_buffer;
        slot.report_length = source[i].interrupt_length;
        slot.active = source[i].occupied && !source[i].cleanup_done;
        destination[i] = slot;
    }
}

bool before_input_mapping(const UpstreamControllerView* controllers,
                          uint32_t count,
                          void* driver_extension) {
    if (!controllers || !driver_extension || count == 0 || count > 4)
        return false;

    native_controller_core::NativeSlot slots[4] = {};
    build_slots(controllers, count, slots);
    return native_controller_core::observe_interrupt(
        slots, count, driver_extension);
}

void before_controller_cleanup(const UpstreamControllerView* controllers,
                               uint32_t count,
                               void* device_handle) {
    if (!controllers || !device_handle || count == 0 || count > 4)
        return;

    native_controller_core::NativeSlot slots[4] = {};
    build_slots(controllers, count, slots);
    native_controller_core::observe_remove(slots, count, device_handle);
}

}
