#include "native_controller_core.h"
#include <string.h>

namespace native_controller_core {

int find_by_driver(NativeSlot* slots, uint32_t count, void* driver_extension) {
    if (!slots || !driver_extension) return -1;
    for (uint32_t i = 0; i < count; ++i) {
        if (slots[i].active && slots[i].driver_extension == driver_extension)
            return (int)i;
    }
    return -1;
}

int find_by_handle(NativeSlot* slots, uint32_t count, void* device_handle) {
    if (!slots || !device_handle) return -1;
    for (uint32_t i = 0; i < count; ++i) {
        if (slots[i].active && slots[i].device_handle == device_handle)
            return (int)i;
    }
    return -1;
}

static native_callback_adapter::InterruptContext context_from(
    const NativeSlot& slot) {
    native_callback_adapter::InterruptContext c = {};
    c.device_handle = slot.device_handle;
    c.driver_extension = slot.driver_extension;
    c.vendor_id = slot.vendor_id;
    c.product_id = slot.product_id;
    c.report_buffer = slot.report_buffer;
    c.report_length = slot.report_length;
    return c;
}

bool observe_interrupt(NativeSlot* slots, uint32_t count,
                       void* driver_extension) {
    const int index = find_by_driver(slots, count, driver_extension);
    if (index < 0) return false;
    return native_callback_adapter::observe_valid_interrupt(
        context_from(slots[index]));
}

void observe_remove(NativeSlot* slots, uint32_t count, void* device_handle) {
    const int index = find_by_handle(slots, count, device_handle);
    if (index < 0) return;
    native_callback_adapter::observe_before_remove(context_from(slots[index]));
}

void* detach_report_buffer(NativeSlot& slot) {
    void* report = slot.report_buffer;
    slot.report_buffer = 0;
    return report;
}

}
