/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813E1DC.c
 * Original SHA-256: 27b54fb88607bae000f65cbdf2adb6395c6cd22fae6f76f163a43c11e447fa23
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* 0x0813E1DC..0x0813E346: 362 bytes. */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x24];
} Entry0813E1DC;

typedef struct {
    u8 unknown_00[4];
    u8 count;
    u8 unknown_05[7];
    u8 mode;
    u8 field_0D;
    u8 unknown_0E[2];
    u8 descriptor[8];
    Entry0813E1DC entries[256];
} State0813E1DC;

extern u32 func_08002804(void);
extern void func_0813F080(Entry0813E1DC *entry, void *descriptor,
                         s16 x, u16 y, u16 amount, u32 tier, u8 mode);

void func_0813E1DC(State0813E1DC *state, u16 x, u16 y, u16 amount, u16 count)
{
    u32 first_x;
    u32 second_x;
    u32 first_y;
    u32 second_y;
    u8 index;
    u8 chance;

    if (count > state->count)
        count = state->count;
    if (state->mode != 4)
        return;

    first_x = (u16)(s32)((double)(s16)x * 1.3);
    second_x = (u16)(s32)((double)(s16)x * 1.5);
    first_y = (u16)(s32)((double)(s32)y * 1.3);
    second_y = (u16)(s32)((double)(s32)y * 1.5);

    for (index = 0; index < count; ++index) {
        chance = (s16)func_08002804() % 100;
        if (chance < 30)
            func_0813F080(&state->entries[index], state->descriptor,
                         (s16)x, y, amount, 1, state->field_0D);
        else if (chance < 70)
            func_0813F080(&state->entries[index], state->descriptor,
                         (s16)first_x, first_y, amount, 2, state->field_0D);
        else
            func_0813F080(&state->entries[index], state->descriptor,
                         (s16)second_x, second_y, amount, 3, state->field_0D);
    }
}
