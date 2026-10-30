/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08061350.c
 * Original SHA-256: cf6b2fe1f23f8633b06ddba79bf58be93fc4d3124b755a106039853b86088c74
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 *tilemap;
} DisplayState08061350;

extern DisplayState08061350 data_030008B0;

/* Complete [0x08061350, 0x08061390): 64 bytes, 26 instructions. */
void func_08061350(void)
{
    u16 *destination = data_030008B0.tilemap + 0x58;
    destination[0] = 0xD063;
    destination[1] = 0xD064;
    destination[2] = 0xD065;
    destination += 32;
    *destination++ = 0xD066;
    *destination++ = 0xD067;
    *destination = 0xD068;
}
