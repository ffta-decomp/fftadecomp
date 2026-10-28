/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D6EEC.c
 * Original SHA-256: 2955e4742adbad44e7ee5ba313b6f6e371221f02e49ee0f9b18860b2bc918ee3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D6EEC..0x080D6F64: 120 bytes, 60 instructions. */
void func_080D6EEC(const u8 *source, u16 count, u8 *destination, u8 color)
{
    u8 high_color = color << 4;
    u16 i;

    for (i = 0; i < count; i++) {
        u32 bits = source[i];
        u16 bit;

        *(u32 *)destination = 0;
        for (bit = 0; bit < 8; bit++) {
            if (bits & 1) {
                if (bit & 1) {
                    *destination |= high_color;
                } else {
                    *destination |= color;
                }
            }
            if (bit & 1) {
                destination++;
            }
            bits >>= 1;
        }
    }
}
