#pragma once
#include <stdint.h>
#include "upstream_controller_adapter.h"

namespace interrupt_observer_patch {

// Small facade intended to be called from the adapted upstream interruptHandler.
// The native callback remains responsible for every controller behavior.
bool before_mapping(const upstream_controller_adapter::UpstreamControllerView* controllers,
                    uint32_t controller_count,
                    void* driver_extension);

// Removal counterpart. Must run before upstream destroys the matching slot.
void before_cleanup(const upstream_controller_adapter::UpstreamControllerView* controllers,
                    uint32_t controller_count,
                    void* device_handle);

}
