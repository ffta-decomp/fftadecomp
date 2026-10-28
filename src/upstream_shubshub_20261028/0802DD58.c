/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0802DD58.c
 * Original SHA-256: 1a8216e9729be6e9228dde1a49ce5dfe5a64be1ea2521991446ebf6d96f68a26
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 group : 4;
    u16 count : 7;
    u16 unknown_0B : 5;
    u8 unknown_02[2];
} __attribute__((packed)) GroupRecord;

typedef struct {
    u8 unknown_00[0x104];
    u8 group;
    u8 unknown_105[3];
} UnitRecord;

extern GroupRecord data_02003C3C[];
extern UnitRecord g_state_02000080[];
extern u8 func_080C832C(UnitRecord *unit);
extern u8 func_080C8364(UnitRecord *unit);
extern u8 func_080C8240(UnitRecord *unit);
extern u8 func_080C8260(UnitRecord *unit);
extern u8 func_080C8298(UnitRecord *unit);

/* Complete target: 0x0802DD58..0x0802DE10, 184 bytes. */
u32 func_0802DD58(void)
{
    GroupRecord *group = data_02003C3C;
    u32 count = 0;
    s32 i;
    s32 j;

    for (i = 0; i < 24; i++, group++)
    {
        if (!group->count)
            return count;
        for (j = 0; j < 24; j++)
        {
            UnitRecord *unit = &g_state_02000080[j];

            if (unit->group != 0xFF && unit->group == group->group &&
                func_080C832C(unit) && !func_080C8364(unit) &&
                !func_080C8240(unit) && !func_080C8260(unit) &&
                !func_080C8298(unit))
                count++;
        }
    }
    return count;
}
