/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08035578.c
 * Original SHA-256: cb681603dd5eabe6c0e4838f790e88e0fdaffe72f51c91b3015d1ff37467664e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x08035578, 0x0803559E): 38 bytes, 19 instructions. */
void func_08035578(const u16 *source, u16 *destination, u32 count, u16 offset)
{
    u32 index;

    for (index = 0; index < count; index++) {
        u16 value = *source;

        *destination = value + offset;
        destination++;
        source++;
    }
}
