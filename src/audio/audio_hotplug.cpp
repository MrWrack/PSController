#include "audio_hotplug.h"
#include "audio_manager.h"

namespace {
static const int kMaxTracked = 8;
audio_hotplug::Device g_devices[kMaxTracked] = {};
bool g_used[kMaxTracked] = {};

bool is_controller(audio_hotplug::DeviceKind k) {
    return k == audio_hotplug::DEVICE_DS4 ||
           k == audio_hotplug::DEVICE_DUALSENSE;
}

bool is_inzone(audio_hotplug::DeviceKind k) {
    return k == audio_hotplug::DEVICE_INZONE_H5 ||
           k == audio_hotplug::DEVICE_INZONE_H7 ||
           k == audio_hotplug::DEVICE_INZONE_H9;
}

void refresh() {
    bool controller = false;
    bool aux = false;
    bool inzone = false;

    for (int i = 0; i < kMaxTracked; ++i) {
        if (!g_used[i]) continue;
        const audio_hotplug::Device& d = g_devices[i];
        if (is_controller(d.kind)) {
            controller = true;
            if (d.aux_inserted) aux = true;
        }
        if (is_inzone(d.kind)) inzone = true;
    }

    audio::set_controller_connected(controller);
    audio::set_controller_aux_present(aux);
    audio::set_inzone_present(inzone);
}
}

namespace audio_hotplug {

void reset() {
    for (int i = 0; i < kMaxTracked; ++i) {
        g_used[i] = false;
        g_devices[i] = Device();
    }
    refresh();
}

void on_device_added(const Device& device) {
    if (!device.handle) return;
    for (int i = 0; i < kMaxTracked; ++i) {
        if (g_used[i] && g_devices[i].handle == device.handle) {
            const bool old_aux = g_devices[i].aux_inserted;
            g_devices[i] = device;
            // Preserve jack state unless the caller explicitly supplied it.
            if (is_controller(device.kind) && !device.aux_inserted)
                g_devices[i].aux_inserted = old_aux;
            refresh();
            return;
        }
    }
    for (int i = 0; i < kMaxTracked; ++i) {
        if (!g_used[i]) {
            g_used[i] = true;
            g_devices[i] = device;
            break;
        }
    }
    refresh();
}

void on_device_removed(xbox360_usb::DeviceHandle* handle) {
    if (!handle) return;
    for (int i = 0; i < kMaxTracked; ++i) {
        if (g_used[i] && g_devices[i].handle == handle) {
            g_used[i] = false;
            g_devices[i] = Device();
        }
    }
    refresh();
}

void set_aux_inserted(xbox360_usb::DeviceHandle* handle, bool inserted) {
    if (!handle) return;
    for (int i = 0; i < kMaxTracked; ++i) {
        if (g_used[i] && g_devices[i].handle == handle &&
            is_controller(g_devices[i].kind)) {
            g_devices[i].aux_inserted = inserted;
        }
    }
    refresh();
}

bool inzone_connected() {
    for (int i = 0; i < kMaxTracked; ++i)
        if (g_used[i] && is_inzone(g_devices[i].kind)) return true;
    return false;
}

bool controller_connected() {
    for (int i = 0; i < kMaxTracked; ++i)
        if (g_used[i] && is_controller(g_devices[i].kind)) return true;
    return false;
}

bool controller_aux_connected() {
    for (int i = 0; i < kMaxTracked; ++i)
        if (g_used[i] && is_controller(g_devices[i].kind) &&
            g_devices[i].aux_inserted) return true;
    return false;
}

}
