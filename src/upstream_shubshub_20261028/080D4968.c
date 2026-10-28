/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D4968.c
 * Original SHA-256: 150b55cca1ec4a327c8a8762329959a8bb21546a4597d4133721dc0610846579
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D4968..0x080D499C: 52 bytes. */
s16 func_080D4968(const u32 *handles, u16 count)
{
    s16 i;

    for (i = 0; i < count; i++) {
        if (handles[i] == 0)
            return i;
    }
    return -1;
}
