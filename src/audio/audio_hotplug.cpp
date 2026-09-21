#include "audio_hotplug.h"
#include "audio_manager.h"
#include "../controller/playstation_devices.h"

namespace {
static const int kMaxTracked = 8;
audio_hotplug::Device g_devices[kMaxTracked] = {};
bool g_used[kMaxTracked] = {};

void refresh() {
    bool aux = false;
    bool inzone = false;
    for (int i = 0; i < kMaxTracked; ++i) {
        if (!g_used[i]) continue;
        const audio_hotplug::DeviceKind k = g_devices[i].kind;
        if (k == audio_hotplug::DEVICE_DS4 ||
            k == audio_hotplug::DEVICE_DUALSENSE)
            aux = true;
        if (k == audio_hotplug::DEVICE_INZONE_H5 ||
            k == audio_hotplug::DEVICE_INZONE_H7 ||
            k == audio_hotplug::DEVICE_INZONE_H9)
            inzone = true;
    }
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
            g_devices[i] = device;
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

bool inzone_connected() {
    for (int i = 0; i < kMaxTracked; ++i)
        if (g_used[i] && (g_devices[i].kind == DEVICE_INZONE_H5 ||
                          g_devices[i].kind == DEVICE_INZONE_H7 ||
                          g_devices[i].kind == DEVICE_INZONE_H9))
            return true;
    return false;
}

bool controller_aux_connected() {
    for (int i = 0; i < kMaxTracked; ++i)
        if (g_used[i] && (g_devices[i].kind == DEVICE_DS4 ||
                          g_devices[i].kind == DEVICE_DUALSENSE))
            return true;
    return false;
}

}
