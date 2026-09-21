#pragma once
#include "first_xex_adapter.h"

namespace target_entry_contract {

enum EntryEvent {
    ENTRY_PROCESS_ATTACH = 1,
    ENTRY_PROCESS_DETACH = 2,
    ENTRY_OTHER = 3
};

struct Result {
    bool accepted;
    first_xex_adapter::Status diagnostic_status;
};

Result dispatch(EntryEvent event, const first_xex_adapter::Services* services);

}
