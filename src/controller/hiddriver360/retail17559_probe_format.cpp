#include "retail17559_probe_format.h"

namespace retail17559_probe_format {
static char hex_digit(uint8_t v) { return v < 10 ? char('0' + v) : char('A' + (v - 10)); }

bool format_target(const char* name,
                   const retail17559_probe::TargetBytes& t,
                   char* out,
                   uint32_t cap) {
    if (!name || !out || cap == 0 || !t.valid || t.length == 0 ||
        t.length > retail17559_probe::MAX_BYTES) return false;

    uint32_t p = 0;
    while (*name) {
        if (p + 1 >= cap) return false;
        out[p++] = *name++;
    }
    const char prefix[] = " @";
    for (uint32_t i=0;i<2;i++) { if (p+1>=cap) return false; out[p++]=prefix[i]; }

    for (int shift=28; shift>=0; shift-=4) {
        if (p+1>=cap) return false;
        out[p++] = hex_digit((uint8_t)((t.address >> shift) & 0xF));
    }
    if (p+2>=cap) return false;
    out[p++]=':'; out[p++]=' ';

    for (uint32_t i=0;i<t.length;i++) {
        if (p+3>=cap) return false;
        out[p++]=hex_digit((uint8_t)(t.bytes[i] >> 4));
        out[p++]=hex_digit((uint8_t)(t.bytes[i] & 0xF));
        if (i + 1 < t.length) out[p++]=' ';
    }
    out[p]=0;
    return true;
}
}
