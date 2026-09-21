#include <cstdio>
#include "../src/controller/hiddriver360/target_entry_contract.h"

static unsigned int kernel_17559() { return 17559u; }
static unsigned int wrong_kernel() { return 12345u; }
static bool read_memory(unsigned int, void* out, unsigned int size) {
    unsigned char* p = static_cast<unsigned char*>(out);
    for (unsigned int i = 0; i < size; ++i) p[i] = static_cast<unsigned char>(i);
    return true;
}
static void log_line(const char* line) { std::printf("%s\n", line); }

int main() {
    first_xex_adapter::Services ok = { &kernel_17559, &read_memory, &log_line };
    target_entry_contract::Result a =
        target_entry_contract::dispatch(target_entry_contract::ENTRY_PROCESS_ATTACH, &ok);
    if (!a.accepted) return 10;

    target_entry_contract::dispatch(target_entry_contract::ENTRY_PROCESS_DETACH, 0);

    first_xex_adapter::Services bad = { &wrong_kernel, &read_memory, &log_line };
    target_entry_contract::Result b =
        target_entry_contract::dispatch(target_entry_contract::ENTRY_PROCESS_ATTACH, &bad);
    if (b.accepted) return 11;
    if (b.diagnostic_status != first_xex_adapter::STATUS_UNSUPPORTED_KERNEL) return 12;

    std::puts("[PASS] Target entry contract fails closed and accepts 17559 diagnostics.");
    return 0;
}
