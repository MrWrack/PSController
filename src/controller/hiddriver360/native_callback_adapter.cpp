#include "native_callback_adapter.h"

namespace native_callback_adapter {

static native_hook_bridge::NativeControllerView view_from(
    const InterruptContext& c) {
    native_hook_bridge::NativeControllerView v = {};
    v.device_handle = c.device_handle;
    v.driver_extension = c.driver_extension;
    v.vendor_id = c.vendor_id;
    v.product_id = c.product_id;
    v.report_buffer = c.report_buffer;
    v.report_length = c.report_length;
    v.active = true;
    return v;
}

bool observe_valid_interrupt(const InterruptContext& context) {
    if (!context.device_handle || !context.driver_extension ||
        !context.report_buffer || context.report_length == 0) {
        return false;
    }
    return native_hook_bridge::on_interrupt(view_from(context));
}

void observe_before_remove(const InterruptContext& context) {
    if (!context.device_handle) return;
    native_hook_bridge::on_remove(view_from(context));
}

}
