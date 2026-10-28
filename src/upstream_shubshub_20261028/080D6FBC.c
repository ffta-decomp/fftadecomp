/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D6FBC.c
 * Original SHA-256: c11dd449c3b073dbbf064015d703f237967deecb2dd9d4769d3aca4d8874a358
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

void func_080D6FBC(const u8 *input, u16 length, u8 *output)
{
    u16 i;

    for (i = 0; i < length; i += 3) {
        const u8 *chunk = input + i;
        u32 packed = chunk[0] | (chunk[1] << 8) | (chunk[2] << 16);
        u16 j;

        *output = 0;
        for (j = 0; j < 8; j++) {
            u8 value = packed & 7;

            if (j & 1) {
                *output |= value << 4;
                output++;
                *output = 0;
            } else {
                *output |= value;
            }
            packed >>= 3;
        }
    }
}
