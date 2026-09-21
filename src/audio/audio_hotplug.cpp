#include "audio_hotplug.h"
#include "audio_manager.h"

namespace {
static const int kMaxTracked = 8;
audio_hotplug::Device g_devices[kMaxTracked] = {};
bool g_used[kMaxTracked] = {};

bool is_controller(audio_hotplug::DeviceKind k) {
    return k == audio_hotplug::DEVICE_DS4 || k == audio_hotplug::DEVICE_DUALSENSE;
}
bool is_inzone(audio_hotplug::DeviceKind k) {
    return k == audio_hotplug::DEVICE_INZONE_H5 ||
           k == audio_hotplug::DEVICE_INZONE_H7 ||
           k == audio_hotplug::DEVICE_INZONE_H9;
}
bool is_wireless_usb_headset(audio_hotplug::DeviceKind k) {
    return is_inzone(k) || k == audio_hotplug::DEVICE_LOGITECH_G733;
}

void refresh() {
    bool controller = false, aux = false, wireless = false;
    for (int i = 0; i < kMaxTracked; ++i) {
        if (!g_used[i]) continue;
        const audio_hotplug::Device& d = g_devices[i];
        if (is_controller(d.kind)) {
            controller = true;
            if (d.aux_inserted) aux = true;
        }
        if (is_wireless_usb_headset(d.kind)) wireless = true;
    }
    audio::set_controller_connected(controller);
    audio::set_controller_aux_present(aux);
    // Existing manager name is retained for ABI/source compatibility; this
    // flag now means a priority USB wireless headset (INZONE or G733).
    audio::set_inzone_present(wireless);
}
}

namespace audio_hotplug {
void reset() {
    for (int i = 0; i < kMaxTracked; ++i) { g_used[i] = false; g_devices[i] = Device(); }
    refresh();
}
void on_device_added(const Device& device) {
    if (!device.handle) return;
    for (int i = 0; i < kMaxTracked; ++i) {
        if (g_used[i] && g_devices[i].handle == device.handle) {
            const bool old_aux = g_devices[i].aux_inserted;
            g_devices[i] = device;
            if (is_controller(device.kind) && !device.aux_inserted) g_devices[i].aux_inserted = old_aux;
            refresh(); return;
        }
    }
    for (int i = 0; i < kMaxTracked; ++i) if (!g_used[i]) {
        g_used[i] = true; g_devices[i] = device; break;
    }
    refresh();
}
void on_device_removed(xbox360_usb::DeviceHandle* handle) {
    if (!handle) return;
    for (int i = 0; i < kMaxTracked; ++i) if (g_used[i] && g_devices[i].handle == handle) {
        g_used[i] = false; g_devices[i] = Device();
    }
    refresh();
}
void set_aux_inserted(xbox360_usb::DeviceHandle* handle, bool inserted) {
    if (!handle) return;
    for (int i = 0; i < kMaxTracked; ++i)
        if (g_used[i] && g_devices[i].handle == handle && is_controller(g_devices[i].kind))
            g_devices[i].aux_inserted = inserted;
    refresh();
}
bool wireless_usb_headset_connected() {
    for (int i = 0; i < kMaxTracked; ++i)
        if (g_used[i] && is_wireless_usb_headset(g_devices[i].kind)) return true;
    return false;
}
bool inzone_connected() {
    for (int i = 0; i < kMaxTracked; ++i) if (g_used[i] && is_inzone(g_devices[i].kind)) return true;
    return false;
}
bool logitech_g733_connected() {
    for (int i = 0; i < kMaxTracked; ++i)
        if (g_used[i] && g_devices[i].kind == DEVICE_LOGITECH_G733) return true;
    return false;
}
bool controller_connected() {
    for (int i = 0; i < kMaxTracked; ++i) if (g_used[i] && is_controller(g_devices[i].kind)) return true;
    return false;
}
bool controller_aux_connected() {
    for (int i = 0; i < kMaxTracked; ++i)
        if (g_used[i] && is_controller(g_devices[i].kind) && g_devices[i].aux_inserted) return true;
    return false;
}
}
