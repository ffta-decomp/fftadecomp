/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08002CB0.c
 * Original SHA-256: f351e78a35f7a209f2843088450768f7041e87d1f127766c8321abcdebd567b4
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 08002CB0..08002D04: 84 bytes. Compare bounded halfword strings. */
s32 func_08002CB0(const u16 *left, const u16 *right, s16 count)
{
    while (--count != -1) {
        if (*left > *right)
            return 1;
        if (*left < *right++)
            return -1;
        if (*left++ == 0)
            break;
    }

    return 0;
}
