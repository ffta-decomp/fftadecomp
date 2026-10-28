/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080030D8.c
 * Original SHA-256: 0f0c79a79bdb08f979e03da2bc4ec1e9e089a108b2aa195d3a7a5ac00130dba6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: [0x080030D8, 0x08003134), 92 bytes, 44 instructions. */
void func_080030D8(s16 value, u16 *buffer, u16 attributes)
{
    int remaining;

    buffer += 6;
    *buffer-- = 0;
    remaining = 6;
    do {
        *buffer-- = ((value & 7) + '0') | attributes;
        remaining--;
    } while ((value = (value >> 3) & 0x1fff) != 0);

    while (remaining-- != 0)
        *buffer-- = ' ' | attributes;
}
