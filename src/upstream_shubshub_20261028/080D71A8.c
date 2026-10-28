/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D71A8.c
 * Original SHA-256: 9e24af6d71d9ecb60a2e96ab59dc277987646689855bd45823e54b5df7c51da2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D71A8..0x080D721E: 118 bytes, 59 instructions. */
void func_080D71A8(const u8 *source, u16 count, u8 *destination, u16 offset)
{
    u16 i;

    for (i = 0; i < count; i += 3) {
        const u8 *input = source + i;
        u32 bits = input[0] | (input[1] << 8) | (input[2] << 16);
        u16 pixel;

        for (pixel = 0; pixel < 4; pixel++) {
            *destination = bits & 0x3F;
            if (bits & 0x3F) {
                *destination += offset;
            }
            destination++;
            bits >>= 6;
        }
    }
}
