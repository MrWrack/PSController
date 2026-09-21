#pragma once
#include <stdint.h>
#include "native_controller_core.h"

namespace upstream_controller_adapter {

// Layout-independent view of the fields PSController needs from upstream's
// Controller + HidControllerExtension. The real XDK-facing translation stays
// in the eventual native entry unit.
struct UpstreamControllerView {
    void* device_handle;
    void* controller_driver;
    uint16_t vendor_id;
    uint16_t product_id;
    void* interrupt_buffer;
    uint32_t interrupt_length;
    bool cleanup_done;
    bool occupied;
};

void build_slots(const UpstreamControllerView* source,
                 uint32_t count,
                 native_controller_core::NativeSlot* destination);

// Returns false if the driver extension cannot be matched safely.
// The caller must still preserve upstream mapping/currentState/requeue logic.
bool before_input_mapping(const UpstreamControllerView* controllers,
                          uint32_t count,
                          void* driver_extension);

// Notify AUX/audio before upstream removal destroys controller state.
void before_controller_cleanup(const UpstreamControllerView* controllers,
                               uint32_t count,
                               void* device_handle);

}
