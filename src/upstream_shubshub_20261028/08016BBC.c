/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08016BBC.c
 * Original SHA-256: 6043a365d09d946138ed782e25deda5d6750007f00fbb6be4acf195c77e21032
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08016BBC..0x08016BD8: 28 bytes / 14 instructions. */
struct Window08016BBC {
    u8 unknown_00[4];
    void *secondary_buffer;
    u8 unknown_08[0x0A];
    u8 width;
    u8 height;
};

u16 func_08016BBC(const struct Window08016BBC *window)
{
    u16 size = window->width * window->height * 2;

    if (window->secondary_buffer != 0)
        size *= 2;
    return size;
}
