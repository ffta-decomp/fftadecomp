/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08061390.c
 * Original SHA-256: 06e0d9594137ea6d564728b5fc18a5aa34797dff8fbeae671b20aa6ea1618e75
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 *tilemap;
} DisplayState08061390;

extern DisplayState08061390 data_030008B0;

/* Complete [0x08061390, 0x080613D0): 64 bytes, 26 instructions. */
void func_08061390(void)
{
    u16 *destination = data_030008B0.tilemap + 0x3A;

    destination[0] = 0xD063;
    destination[1] = 0xD064;
    destination[2] = 0xD065;
    destination += 32;
    *destination++ = 0xD066;
    *destination++ = 0xD067;
    *destination = 0xD068;
}
