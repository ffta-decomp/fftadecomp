/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08089B0C.c
 * Original SHA-256: 02033e47682fd4a0b84335afa245a797e476aef5b59159550bcf006d3be649a6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08089B0C..0x08089B48: 60 bytes. */
void func_08089B0C(u16 *tiles, u16 filled, u16 length, u16 tile)
{
    u16 *cursor = tiles;
    u16 empty = length - filled;
    u16 column;

    for (column = 0; column < length; ++column) {
        if (column >= empty)
            *cursor = tile + 0xDB;
        else
            *cursor = 0;
        ++cursor;
    }
}
