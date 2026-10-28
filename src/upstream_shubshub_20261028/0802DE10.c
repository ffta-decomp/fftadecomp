/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0802DE10.c
 * Original SHA-256: f112da8e0a31495b81fd4522f59705103316629efa62fdde80e588a451de92ce
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct SearchRecord {
    u8 unknown_00[0x104];
    u8 identifier;
    u8 unknown_105[3];
} SearchRecord;

typedef struct __attribute__((packed)) SearchSelector {
    u16 identifier : 4;
    u16 count : 7;
    u16 unknown_0B : 5;
    u8 unknown_02[2];
} SearchSelector;

extern SearchRecord g_state_02000080[24];
extern u8 func_080C832C(SearchRecord *record);

/* 0802DE10..0802DE58: 72 bytes, 33 instructions. */
SearchRecord *func_0802DE10(const SearchSelector *selector)
{
    SearchRecord *record = g_state_02000080;
    s32 index;

    for (index = 0; index < 24; index++, record++) {
        if (record->identifier != 0xFF &&
            record->identifier == selector->identifier &&
            func_080C832C(record))
            return record;
    }
    return 0;
}
