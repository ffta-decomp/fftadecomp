/* Contributed by gg; original source and attribution follow. */
/* SceneTaskDependency_0002ACD4
   entry 0x0802ACD4, 128 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08054204.c
 * Original SHA-256: 31234aaf6d93cbd9e84b27c118a223d21001f4b505451ee2634df13f98adf223
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* ---- inlined ffta.h ---- */
#ifndef FFTA_SHIM_H
#define FFTA_SHIM_H
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
#endif

typedef struct {
    u8 unknown_00[0x0000000C];
    u16 *tiles;
    u8 unknown_10[5];
    u8 width;
    u8 unknown_16[9];
    u8 palette;
} Window;

/* Complete target: [0x08054204, 0x08054284), 128 bytes, 62 instructions. */
void f_target(Window *window, s8 row, u8 palette, u8 column, u8 length)
{
    u16 rowIndex = row * 2;
    u16 *tiles = window->tiles + column + rowIndex * window->width;
    s32 i;
    s32 j;

    if (palette == 0x000000FF)
        palette = window->palette;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < length; j++)
            tiles[j] = (tiles[j] & 0xFFF) | (palette << 12);
        tiles += window->width;
    }
}
