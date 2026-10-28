/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081481AC.c
 * Original SHA-256: cd792365d27006b0a1cc528ddf473d64e8fb39fae196acf6b639f87dbd3812d7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 081481AC .. 08148214: 104 bytes. */
void func_081481AC(const u16 *source, u16 *destination, u16 count)
{
    u16 index;

    for (index = 0; index < count; index++) {
        u16 color = source[index];
        u16 red = color & 0x1F;
        u16 green = (color & 0x3E0) >> 5;
        u16 blue = (color & 0x7C00) >> 10;
        u16 average = (red + green + blue) / 3;

        destination[index] = average | (average << 5) | (average << 10);
    }
}
