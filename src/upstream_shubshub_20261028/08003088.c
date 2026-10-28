/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08003088.c
 * Original SHA-256: 989cf583d8fc0ff6d8a588f294fece4dc6aceb40d4db3e4057b68146a596f2e2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: [0x08003088, 0x080030D8), 80 bytes, 38 instructions. */
void func_08003088(s16 value, u8 *buffer)
{
    int remaining;

    buffer += 6;
    *buffer-- = 0;
    remaining = 6;
    do {
        *buffer-- = (value & 7) + '0';
        remaining--;
    } while ((value = (value >> 3) & 0x1fff) != 0);

    while (remaining-- != 0)
        *buffer-- = ' ';
}
