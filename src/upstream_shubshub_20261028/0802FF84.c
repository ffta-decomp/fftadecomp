/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0802FF84.c
 * Original SHA-256: 29c57ddaa8a8b299370ea6ba41141f4aca238f7dfbec2c2a330bb243c724e481
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 group : 4;
    u16 count : 7;
    u16 unknown_0b : 5;
    u8 unknown_02[2];
} __attribute__((packed)) GroupRecord;

typedef struct {
    u8 unknown_00[0x104];
    u8 group;
    u8 unknown_105[3];
} UnitRecord;

extern GroupRecord data_02003C3C[];
extern UnitRecord g_state_02000080[];
extern u32 func_080C832C(UnitRecord *unit);
extern u32 func_080C8364(UnitRecord *unit);
extern u32 func_080C8240(UnitRecord *unit);
extern u32 func_080C8260(UnitRecord *unit);
extern u32 func_080C8298(UnitRecord *unit);

/* Complete target: [0x0802FF84, 0x08030044), 192 bytes. */
GroupRecord *func_0802FF84(s32 ordinal)
{
    GroupRecord *group = data_02003C3C;
    s32 count = 0;
    s32 i;
    s32 j;

    for (i = 0; i < 24; i++, group++) {
        if (!group->count)
            return 0;
        for (j = 0; j < 24; j++) {
            UnitRecord *unit = &g_state_02000080[j];
            if (unit->group != 0xff && unit->group == group->group &&
                (u8)func_080C832C(unit) && !(u8)func_080C8364(unit) &&
                !(u8)func_080C8240(unit) && !(u8)func_080C8260(unit) &&
                !(u8)func_080C8298(unit)) {
                if (count == ordinal)
                    return group;
                count++;
            }
        }
    }
    return 0;
}
