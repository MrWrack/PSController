#pragma once
#include "retail17559_hooks.h"

namespace native_originals {

// Typed call-through is deliberately kept outside the generic detour storage.
// Hook bodies should cast only to the exact upstream/native signature they own.
template <typename Fn>
Fn hid_add() {
    return reinterpret_cast<Fn>(retail17559_hooks::originals().hid_add);
}

template <typename Fn>
Fn hid_remove() {
    return reinterpret_cast<Fn>(retail17559_hooks::originals().hid_remove);
}

template <typename Fn>
Fn xinput_read() {
    return reinterpret_cast<Fn>(retail17559_hooks::originals().xinput_read);
}

template <typename Fn>
Fn xam_caps() {
    return reinterpret_cast<Fn>(retail17559_hooks::originals().xam_caps);
}

template <typename Fn>
Fn xam_set_state() {
    return reinterpret_cast<Fn>(retail17559_hooks::originals().xam_set_state);
}

}
