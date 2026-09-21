#include "runtime_bridge.h"
#include "../../audio/hiddriver_audio_bridge.h"

namespace hiddriver_runtime {

bool observe_interrupt(const ControllerSlot& slot) {
    if (!slot.active || !slot.handle || !slot.driver_extension ||
        !slot.report_buffer || slot.report_length == 0) {
        return false;
    }

    hiddriver_audio_bridge::on_input_report(
        slot.handle,
        slot.vendor_id,
        slot.product_id,
        slot.report_buffer,
        slot.report_length);

    // Important: true only means the observer ran. The native hiddriver360
    // mapping/currentState/requeue path must continue regardless.
    return true;
}

void observe_remove(const ControllerSlot& slot) {
    if (!slot.handle) return;
    hiddriver_audio_bridge::on_device_removed(slot.handle);
}

}
