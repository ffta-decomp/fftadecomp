/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08002C6C.c
 * Original SHA-256: 1a996e26dd4810558d0ded33b8fc15feb0fa45cd8ff3016e50a839aef9458c27
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 08002C6C..08002CB0: 68 bytes. Append up to count UTF-16 code units. */
u16 *func_08002C6C(u16 *destination, const u16 *source, u16 count)
{
    s16 remaining = count;
    u16 *original = destination;

    while (*destination != 0)
        destination++;

    while (--remaining != -1) {
        if ((*destination++ = *source++) == 0)
            break;
    }

    return original;
}
