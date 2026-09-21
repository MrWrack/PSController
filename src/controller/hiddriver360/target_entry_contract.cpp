#include "target_entry_contract.h"

namespace target_entry_contract {

Result dispatch(EntryEvent event, const first_xex_adapter::Services* services) {
    Result result = {};
    result.accepted = false;
    result.diagnostic_status = first_xex_adapter::STATUS_NOT_RUN;

    if (event == ENTRY_PROCESS_ATTACH) {
        if (!services) {
            result.diagnostic_status = first_xex_adapter::STATUS_INVALID_SERVICES;
            return result;
        }
        result.diagnostic_status = first_xex_adapter::process_attach(*services);
        result.accepted = (result.diagnostic_status == first_xex_adapter::STATUS_OK);
        return result;
    }

    if (event == ENTRY_PROCESS_DETACH) {
        first_xex_adapter::process_detach();
        result.accepted = true;
        return result;
    }

    // Thread attach/detach and unknown loader events are deliberately ignored
    // by the portable contract. The native shim decides how its verified ABI
    // maps real loader reason values to these events.
    result.accepted = true;
    return result;
}

}
