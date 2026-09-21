#pragma once
#include <stdint.h>
#include "../../usb/xbox360_usb_bridge.h"

namespace hiddriver_runtime {

struct ControllerSlot {
    xbox360_usb::DeviceHandle* handle;
    void* driver_extension;
    uint16_t vendor_id;
    uint16_t product_id;
    void* report_buffer;
    uint32_t report_length;
    bool active;
};

// Called from the native USB interrupt completion before normal mapping.
// Returns false only when the slot/report is invalid. It never consumes input.
bool observe_interrupt(const ControllerSlot& slot);

// Called before the native controller slot is cleared/freed.
void observe_remove(const ControllerSlot& slot);

}
