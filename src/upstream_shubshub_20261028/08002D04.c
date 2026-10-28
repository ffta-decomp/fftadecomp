/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08002D04.c
 * Original SHA-256: 60c835b21b35819e058ffb29c67604e800da684c79766abe8b395031d1f97276
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08002D04 - 92 bytes. Copy a bounded halfword string and zero-fill the remainder. */
u16 *func_08002D04(u16 *destination, const u16 *source, s16 count)
{
    u16 *start = destination;

    while (--count != -1) {
        if ((*destination++ = *source++) == 0)
            break;
    }
    while (count-- > 0)
        *destination++ = 0;
    return start;
}
