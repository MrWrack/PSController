#pragma once
#include <stdint.h>
#include "native_callback_adapter.h"

namespace native_controller_core {

struct NativeSlot {
    void* device_handle;
    void* driver_extension;
    uint16_t vendor_id;
    uint16_t product_id;
    void* report_buffer;
    uint32_t report_length;
    bool active;
};

// Finds a slot by driver extension without ever returning an invalid index.
int find_by_driver(NativeSlot* slots, uint32_t count, void* driver_extension);

// Finds a slot by native device handle.
int find_by_handle(NativeSlot* slots, uint32_t count, void* device_handle);

// Observer entry used by the real interrupt callback after native validation.
// This never consumes input; caller must continue normal mapping/requeue.
bool observe_interrupt(NativeSlot* slots, uint32_t count, void* driver_extension);

// Observer entry used immediately before native removal/cleanup.
void observe_remove(NativeSlot* slots, uint32_t count, void* device_handle);

// Safe helper for cleanup ordering. Saves report_buffer before clearing slot.
void* detach_report_buffer(NativeSlot& slot);

}
