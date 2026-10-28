/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D702C.c
 * Original SHA-256: 9088fd6e973f30fcc85e39fddf2a04c3cc618beb539780e29dec01224da0ef55
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D702C..0x080D7080: 84 bytes. */
void func_080D702C(const u8 *source, u16 count, u8 *destination,
                   u8 foreground, u8 palette)
{
    u16 i;
    u16 bit;
    u8 value;

    palette <<= 4;
    for (i = 0; i < count; i++) {
        value = source[i];
        for (bit = 0; bit < 8; bit++) {
            if (value & 1)
                *destination = palette | foreground;
            else
                *destination = 0;
            destination++;
            value >>= 1;
        }
    }
}
