#pragma once
#include <stdint.h>
#include "native_originals.h"
#include "interrupt_observer_patch.h"

namespace native_hook_bodies {

// These signatures mirror the portions already established from upstream
// hiddriver360. XDK-specific typedefs remain in the final native build unit.
typedef int (*HidRemoveOriginal)(void* device_handle);

struct ControllerSnapshot {
    upstream_controller_adapter::UpstreamControllerView views[4];
    uint32_t count;
};

// Snapshot provider is owned by the adapted hiddriver360 runtime.
typedef bool (*SnapshotFn)(ControllerSnapshot* out);
typedef void (*RemoveOwnedFn)(void* device_handle);

struct RuntimeApi {
    SnapshotFn snapshot;
    RemoveOwnedFn remove_owned;
};

void bind_runtime(const RuntimeApi& api);

// Observer-only entry used by the adapted interruptHandler after it has found
// a valid controller slot. Never use the return value to consume controller input.
void observe_interrupt(void* driver_extension);

// Removal hook preserves upstream call-through: owned hiddriver devices are
// cleaned by the runtime; all other devices go to the original Xbox handler.
int hid_remove(void* device_handle);

}
