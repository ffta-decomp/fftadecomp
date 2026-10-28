/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080539B4.c
 * Original SHA-256: 67363c9872ad9669e311f043b096c161837205237127cef6a4fc849e221cd361
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x080539B4, 0x08053AA0): 236 bytes, 108 instructions. */
typedef struct {
    u8 unknown_00[0x0C];
    u16 *tiles;
    u8 unknown_10[5];
    u8 count;
    u8 unknown_16[6];
    u16 tile;
    u8 unknown_1E;
    u8 palette;
} TileRun080539B4;

typedef struct {
    u8 unknown_00[0x10];
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u8 unknown_14[0x18];
    TileRun080539B4 run;
} MenuState080539B4;

extern u8 func_080CB99C(u16);
extern u8 func_080CCA20(u16);
extern void func_08054314(TileRun080539B4 *, void *, u8, u16, u32);
extern void func_0802AB64(TileRun080539B4 *, u16, u16, u8, u8, u16, u8);
extern void func_0802ACA0(u16 *, u16, u8, u8);
extern void func_08029730(u16 *, u32, u8);
extern void func_0802AC14(MenuState080539B4 *, u16 *, u8, u8, u8);

void func_080539B4(MenuState080539B4 *state, void *text, u16 entry)
{
    u8 palette;

    if (entry > 0x55)
        palette = func_080CB99C(0x18A) + 13;
    else
        palette = func_080CB99C(0x189) + 13;

    func_08054314(&state->run, text, 0, entry, 5);
    func_0802AB64(&state->run, state->run.count + 3, state->run.tile, state->width,
                  2, palette, 0);
    func_0802AB64(&state->run, state->run.count + 5, state->run.tile + 4, state->width,
                  state->run.count - 2, state->run.palette, 1);
    func_0802ACA0(&state->run.tiles[state->width * 3 + 4], 0x81, 13, 4);
    func_08029730(&state->run.tiles[state->width * 3 + 8], 1,
                  func_080CCA20(entry));
    func_0802AC14(state, state->run.tiles, state->x, state->y, state->height - 1);
}
