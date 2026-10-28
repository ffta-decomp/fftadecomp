/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D7080.c
 * Original SHA-256: 1eae4e0911493b4c6de7c331dd88aec9b61988af3f2564fced407c758072942f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D7080..0x080D70D8: 88 bytes, 44 instructions. */
void func_080D7080(const u8 *source, u16 count, u8 *destination, u8 palette)
{
    u8 high_palette = palette << 4;
    u16 i;

    for (i = 0; i < count; i++) {
        u32 bits = source[i];
        u16 pixel;

        for (pixel = 0; pixel < 4; pixel++) {
            *destination = bits & 3;
            if (*destination) {
                *destination |= high_palette;
            }
            destination++;
            bits >>= 2;
        }
    }
}
