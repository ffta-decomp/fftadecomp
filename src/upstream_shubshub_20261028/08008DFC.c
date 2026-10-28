/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08008DFC.c
 * Original SHA-256: 338ec3c0066fa28403ba4d346ce908b6b0eb97aa5c43bc1a2f86d88d8e597bd2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* 0x08008DFC..0x08008E78: 124 target bytes, including four trailing literals. */
#include "ffta.h"

typedef struct {
    u16 *tiles;
    u8 unknown_04[12];
    u8 column;
    u8 row;
    u8 width;
} Control08008DFC;

typedef struct {
    u8 unknown_00[0x2c4];
    Control08008DFC control;
} State08008DFC;

u8 func_08017180(Control08008DFC *control);
u16 func_080161A0(u8 column, u8 row, u8 stride);

u16 func_08008DFC(u32 context)
{
    Control08008DFC *control = &(*(State08008DFC **)0x02009188)->control;
    u8 complete = func_08017180(control);

    if (complete) {
        s32 count = control->width - 2;
        u16 *destination = control->tiles +
            func_080161A0(control->column + 1, control->row + 14, 32);
        s32 index;

        for (index = 0; index < count; index++)
            destination[index] = 0xc050;
        destination[-1] = 0xc051;
        destination[count] = 0xc451;
    }

    return complete;
}
