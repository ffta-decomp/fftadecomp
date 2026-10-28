/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080681C4.c
 * Original SHA-256: a7d5db65f2eafd59d0cab86840d901ce2d499bcaccfb4ee6c5fada7a8be8466a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 *tiles;
} TileMap080681C4;

extern TileMap080681C4 data_03000990;
extern TileMap080681C4 data_030008B0;
extern const u16 data_083AF62C[80];
extern const u16 data_083AF6CC[33];
extern u16 func_080161A0(u8 x, u8 y, u8 width);

/* Complete target [0x080681C4, 0x080682E4): 288 bytes, 127 instructions. */
void func_080681C4(void)
{
    u16 *destination;
    const u16 *source;
    s32 row;
    s32 column;
    s32 index;

    destination = data_03000990.tiles + func_080161A0(1, 11, 32);
    for (row = 0; row < 8; row++) {
        for (column = 13; column >= 0; column--)
            destination[column + row * 32] = 0xc001;
    }

    destination = data_030008B0.tiles + func_080161A0(1, 11, 32);
    source = data_083AF62C;
    index = 0;
    for (row = 0; row < 8; row++) {
        for (column = 0; column < 10; column++) {
            destination[column + row * 32] = source[index] + 0x300;
            index++;
        }
    }

    destination = data_03000990.tiles + func_080161A0(15, 11, 32);
    for (row = 0; row < 3; row++) {
        for (column = 13; column >= 0; column--)
            destination[column + row * 32] = 0xa001;
    }

    destination = data_030008B0.tiles + func_080161A0(15, 11, 32);
    source = data_083AF6CC;
    index = 0;
    for (row = 0; row < 3; row++) {
        for (column = 0; column < 11; column++) {
            destination[column + row * 32] = source[index] + 0x300;
            index++;
        }
    }
}
