/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801DC7C.c
 * Original SHA-256: 88e2dda271b8cb49df1307c687673460069153af40fb1acf68441261a1485729
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0801DC7C..0x0801DCB8: 60 bytes. */
typedef struct {
    u8 unknown_00[0x12];
    u16 current;
} State0801DC7C;

extern State0801DC7C data_02007F10;
extern const u16 data_08425104[];

const u8 *func_0801DC7C(u16 index)
{
    const State0801DC7C *state = &data_02007F10;

    if (state->current == 0xFF)
        return 0;
    if ((s16)index == -1)
        index = state->current;
    {
        const u16 *offsets = data_08425104;
        return (const u8 *)offsets + offsets[(s16)index] + 6;
    }
}
