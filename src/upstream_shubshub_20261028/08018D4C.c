/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08018D4C.c
 * Original SHA-256: da475c8b8498147bf8b78c4fcec6de2ff8532cbda8b229d95867699aae0e7dee
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct NameSelection {
    u8 unknown_00[0x0E];
    u16 table_index;
} NameSelection;

typedef struct NameRecord {
    u8 category;
    u8 text_index;
    u8 unknown_02[2];
} NameRecord;

extern NameSelection g_state_020020D0;
extern const NameRecord data_08528968[];
extern const u8 *const g_table_085567F0[];
extern u16 func_08018C24(u8 *destination, const u8 *source);

/* 08018D4C..08018D80: 52 bytes, 17 instructions. */
u32 func_08018D4C(u8 *destination)
{
    const NameRecord *entry = data_08528968 + g_state_020020D0.table_index;

    func_08018C24(destination, g_table_085567F0[entry->text_index + 0x2AF]);
    return 0;
}
