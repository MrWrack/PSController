#include <cstdio>
#include "../src/controller/hiddriver360/build_info.h"

int main() {
    const build_info::Info info = build_info::first_test();

    std::printf("PSController PC smoke test\n");
    std::printf("Project       : %s\n", info.project);
    std::printf("Target kernel : %u\n", (unsigned)info.target_kernel);
    std::printf("Mode          : %s\n", info.mode);
    std::printf("HID hooks     : %s\n", info.hooks_enabled ? "ON" : "OFF");
    std::printf("Audio         : %s\n", info.audio_enabled ? "ON" : "OFF");

    if (info.target_kernel != 17559u) return 10;
    if (info.hooks_enabled) return 11;
    if (info.audio_enabled) return 12;

    std::puts("[PASS] Safe first-test build identity is valid.");
    return 0;
}
