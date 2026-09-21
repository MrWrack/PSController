#include "native_hook_bridge.h"

namespace native_hook_bridge {

static hiddriver_runtime::ControllerSlot make_slot(
    const NativeControllerView& view) {
    hiddriver_runtime::ControllerSlot slot = {};
    slot.handle =
        reinterpret_cast<xbox360_usb::DeviceHandle*>(view.device_handle);
    slot.driver_extension = view.driver_extension;
    slot.vendor_id = view.vendor_id;
    slot.product_id = view.product_id;
    slot.report_buffer = view.report_buffer;
    slot.report_length = view.report_length;
    slot.active = view.active;
    return slot;
}

bool on_interrupt(const NativeControllerView& view) {
    if (!view.active || !view.device_handle || !view.driver_extension ||
        !view.report_buffer || view.report_length == 0) {
        return false;
    }
    return hiddriver_runtime::observe_interrupt(make_slot(view));
}

void on_remove(const NativeControllerView& view) {
    if (!view.device_handle) return;
    hiddriver_runtime::observe_remove(make_slot(view));
}

}
