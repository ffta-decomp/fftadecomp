/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0806EE98.c
 * Original SHA-256: 5c4cbf5e355d1e5d24bbacc0977e0cdca6d6cd8e09f81de2506c1136140cce43
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0xC];
    u8 width;
    u8 unknown_0D[7];
    u16 *tiles;
} TileGrid0806EE98;

typedef struct {
    u8 selection;
    u8 entries[6];
    u8 count;
    u8 selected_palette;
    u8 other_palette;
    u8 unknown_0A[2];
    TileGrid0806EE98 *grid;
    u16 top[12];
    u16 bottom[12];
    u8 unknown_40[0x38];
    u8 x;
    u8 y;
} Menu0806EE98;

extern const u8 data_08393B46[];
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete target: 0x0806EE98..0x0806EFA8, 272 bytes. */
void func_0806EE98(Menu0806EE98 *state)
{
    u8 entry = 0;
    u8 column;

    for (column = 0; column < state->count * 2; column += 2, ++entry) {
        u8 palette;

        if ((column >> 1) == state->selection)
            palette = state->selected_palette;
        else
            palette = state->other_palette;
        state->top[column] = (data_08393B46[state->entries[entry]] * 4 + 0x10E) | (palette << 12);
        state->top[column + 1] = (data_08393B46[state->entries[entry]] * 4 + 0x10F) | (palette << 12);
        state->bottom[column] = (data_08393B46[state->entries[entry]] * 4 + 0x110) | (palette << 12);
        state->bottom[column + 1] = (data_08393B46[state->entries[entry]] * 4 + 0x111) | (palette << 12);
    }
    func_0814186C(state->top, state->grid->tiles + (state->grid->width * state->y + state->x), state->count * 2);
    func_0814186C(state->bottom, state->grid->tiles + (state->grid->width * (state->y + 1) + state->x), state->count * 2);
}
