/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08058608.c
 * Original SHA-256: 502ffae6eb8ddf21610c34be475fdf85b143c9a12222248a765ca8b350634f98
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

u8 func_08058608(u32 value)
{
    u8 digits = 0;

    do {
        digits++;
        value /= 10;
    } while (value != 0);
    return digits;
}
