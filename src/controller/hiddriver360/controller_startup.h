#pragma once
#include "controller_runtime.h"

namespace controller_startup {

struct PlatformApi {
    unsigned short (*kernel_build)();
    controller_runtime::GetModuleHandleFn get_module;
    controller_runtime::GetProcedureAddressFn get_proc;
    bool (*install_verified_17559_hooks)(
        const controller_runtime::ResolvedExports& exports);
    void (*remove_hooks)();
};

void bind_platform_api(const PlatformApi& api);
bool initialize();
void shutdown();
bool active();
controller_runtime::InitResult last_result();

}
