#pragma once
#include <stdint.h>
#include "runtime_bridge.h"

namespace native_hook_bridge {

// Minimal view passed by the adapted hiddriver360 interrupt/remove hooks.
// It intentionally does not own or mutate native controller state.
struct NativeControllerView {
    void* device_handle;
    void* driver_extension;
    uint16_t vendor_id;
    uint16_t product_id;
    void* report_buffer;
    uint32_t report_length;
    bool active;
};

// Call only after the native callback has found a valid controller index.
// This observes the raw report and always leaves normal mapping/requeue to the
// original hiddriver360 path.
bool on_interrupt(const NativeControllerView& view);

// Call before the native slot/report/driver extension is cleared or freed.
void on_remove(const NativeControllerView& view);

}
