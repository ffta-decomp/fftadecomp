/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D70D8.c
 * Original SHA-256: ce7fbf946a6294ac86e90be74a573017e456c37d52e2746bde7c277be1f8632d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D70D8..0x080D7150: 120 bytes, 60 instructions. */
void func_080D70D8(const u8 *source, u16 count, u8 *destination, u8 palette)
{
    u8 high_palette = palette << 4;
    u16 i;

    for (i = 0; i < count; i += 3) {
        const u8 *input = source + i;
        u32 bits = input[0] | (input[1] << 8) | (input[2] << 16);
        u16 pixel;

        for (pixel = 0; pixel < 8; pixel++) {
            *destination = bits & 7;
            if (bits & 7) {
                *destination |= high_palette;
            }
            destination++;
            bits >>= 3;
        }
    }
}
