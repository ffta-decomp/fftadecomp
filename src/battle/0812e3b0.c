/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0812E3B0.c
 * Original SHA-256: f9971d2904f4c2eb162f510684a10da310a3f4b2ff95364d26ec18308a4770d0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_00[6];
    u8 group;
    u8 unknown_07[0x35];
    u8 entry;
} EntrySelection;

typedef struct {
    u8 unknown_00[4];
    u16 table_index;
} EntryInfo;

typedef struct {
    u8 unknown_00;
    u8 low;
    u8 high;
    u8 unknown_03;
} EntryRecord;

extern const u8 *func_080CD480(u8 group, u8 entry);
extern const EntryRecord data_0852736C[];

/* Target: [0x0812E3B0, 0x0812E3E8), 56 bytes. */
u8 func_0812E3B0(const EntrySelection *selection)
{
    const EntryInfo *info = (const EntryInfo *)func_080CD480(selection->group, selection->entry);

    if (info->table_index != 0) {
        const EntryRecord *record = &data_0852736C[info->table_index];
        u32 low = record->low >> 5;
        u32 high = record->high;

        return ((high & 3) << 3) | low;
    }
    return 0;
}
