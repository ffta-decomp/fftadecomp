/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813B480.c
 * Original SHA-256: 07cfbfe9cd6e32b87b0dbad50e22de8ff501f872c0e2b047dc0ee535198258f7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u32 reference;
    u8 active;
    u8 unknown_05[0x23];
    u16 flags;
    u8 unknown_2A[0xDE];
} UnitRecord;

typedef struct {
    u32 reference;
    u8 unknown_04[12];
} __attribute__((packed)) CompactRecord;

typedef struct {
    u8 unknown_00[0x80];
    UnitRecord records[24];
    u8 unknown_1940[0x1538];
    CompactRecord compactRecords[20];
    u8 unknown_2FB8[12];
    UnitRecord extraRecords[12];
} RecordSet;

typedef struct {
    u8 unknown_00[5];
    u8 enabled;
} UpdateState;

extern UpdateState data_03000ED0;
extern u32 func_0813B57C(u8 mode, void *data);
extern u32 func_080CA1BC(UnitRecord *record);
extern u32 func_080CA1F0(CompactRecord *record);

/* Complete target: [0x0813B480, 0x0813B57C), 252 bytes, 113 instructions. */
u32 func_0813B480(u8 mode, void *data)
{
    RecordSet *set = data;
    CompactRecord *compact;
    u32 result;
    s32 i;

    data_03000ED0.enabled = 0;
    result = func_0813B57C(mode, data);
    for (i = 0; i < 24; i++)
    {
        if (set->records[i].active)
            set->records[i].reference = func_080CA1BC(&set->records[i]);
    }
    for (i = 0; i < 20; i++)
    {
        compact = &set->compactRecords[i];
        if (compact->reference)
            compact->reference = func_080CA1F0(&set->compactRecords[i]);
    }
    if (mode == 2)
    {
        for (i = 0; i < 12; i++)
        {
            if (set->extraRecords[i].active)
                set->extraRecords[i].reference = func_080CA1BC(&set->extraRecords[i]);
        }
    }
    set->records[0].flags &= 0xBFFF;
    data_03000ED0.enabled = 1;
    return result;
}
