#pragma once
#include <stdint.h>
#include "native_hook_bridge.h"

namespace native_callback_adapter {

// Native hiddriver360 supplies these fields after it has resolved a valid
// connectedControllers[] index. Keeping this adapter independent of XDK types
// lets the observer code remain buildable/testable without proprietary headers.
struct InterruptContext {
    void* device_handle;
    void* driver_extension;
    uint16_t vendor_id;
    uint16_t product_id;
    void* report_buffer;
    uint32_t report_length;
};

bool observe_valid_interrupt(const InterruptContext& context);
void observe_before_remove(const InterruptContext& context);

}
