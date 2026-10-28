/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0808B950.c
 * Original SHA-256: 1abd72e4253f4b9ec0171f04f70d19d358cbacae55019806bdbdf7411a9a23d0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0808B950..0x0808B984: 52 bytes, 26 instructions. */
void func_0808B950(u16 *destination, u16 tile, u16 width)
{
    s32 i;

    *destination++ = tile + 1;
    for (i = 1; i < width - 1; i++) {
        *destination++ = tile;
    }
    *destination = (tile + 1) | 0x400;
}
