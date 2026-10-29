/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/0808B890.c
 * Original SHA-256: 5c771fed3554f4a9dcfb379f6cd04e9d68665fe1a1e2c6a30347debed37405c8
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

struct Window0808B890 {
    u8 unknown_00[0x28];
    u8 width;
    u8 unknown_29[0x23];
};

extern struct Window0808B890 data_030009E0[];

/* 0x0808B890 .. 0x0808B8E4: 84 bytes, including literal pools. */
void func_0808B890(int index, u16 *destination, u16 count, u16 flags)
{
    int stride = data_030009E0[index].width;
    int column;

    for (column = 0; column < count; column++, destination++) {
        *destination = (*destination & 0x0FFF) | flags;
        destination[stride] = (destination[stride] & 0x0FFF) | flags;
    }
}
