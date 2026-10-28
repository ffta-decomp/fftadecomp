/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080CA394.c
 * Original SHA-256: 1cd7edb42fb2673dbbbba8e9c27b8bf9b3ed7856d4906b693ff3e0d6c4bdd50c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080CA394..0x080CA3EC: 88 bytes. */
typedef struct {
    u8 unknown_00[0x2A];
    u16 equipment[5];
    u8 unknown_34[9];
    u8 status;
} Unit;

extern s8 func_080C92F0(Unit *unit, u32 field);
extern s32 func_080CA7A4(u16 id, u32 field);

s8 func_080CA394(Unit *unit)
{
    s8 value = func_080C92F0(unit, 30);
    s32 total;
    s32 i;

    if (unit->status == 1)
        value++;
    total = 0;
    for (i = 0; i < 5; i++) {
        if (unit->equipment[i] != 0)
            total += func_080CA7A4(unit->equipment[i], 16);
    }
    value += total;
    if (value < 0)
        value = 0;
    return value;
}
