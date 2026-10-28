/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0806FE1C.c
 * Original SHA-256: df73a0f7c3124e77f85592325a13332859538318740155d63c69b3a21a9e6984
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 phase;
    u8 unknown_02[6];
    u8 panel[4];
    u16 *tiles;
    u8 unknown_10[8];
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u8 unknown_1c[2];
    u8 style;
    u8 unknown_1f[0x61];
    u8 position;
    u8 row;
    u8 unknown_82[2];
    void *first;
    void *second;
    u8 panel_buffer[0x1d4];
    u8 first_buffer[0x800];
    u8 second_buffer[1];
} State0806FE1C;

extern void func_0806FFF8(void *, void *, u8, u8, u8, u8);
extern void func_0802AC14(void *, void *, u8, u8, u8);
extern void func_0802A370(u8, u8, u8, u8);
extern void func_08016800(u16 *, u8, u8, u16, u8, u32, u32, u32);

/* Complete [0x0806FE1C, 0x0806FFAC): 400 bytes, 193 instructions. */
u8 func_0806FE1C(State0806FE1C *state, u8 direction)
{
    u32 done = 0;
    u8 width;

    switch (direction) {
    case 0:
        if (state->phase == 0) {
            state->position = 30;
            state->row = state->y;
            state->phase++;
        } else {
            s8 uncovered;

            state->position -= 4;
            if (state->x > (s8)state->position) {
                state->position = state->x;
                done = 1;
            }
            uncovered = 30 - (state->position + state->width);
            if (uncovered > 0) {
                func_0806FFF8(state->first, state->first_buffer,
                             state->position + state->width, state->y,
                             uncovered, state->height);
                func_0806FFF8(state->second, state->second_buffer,
                             state->position + state->width, state->y,
                             uncovered, state->height);
            }
        }
        break;
    case 1:
        if (state->phase == 0) {
            state->position = state->x;
            state->row = state->y;
            state->phase++;
        } else {
            s8 uncovered;

            state->position += 4;
            if ((s8)state->position > 30) {
                state->position = 30;
                done = 1;
            }
            uncovered = state->position - state->x;
            func_0806FFF8(state->first, state->first_buffer,
                         state->x, state->y, uncovered, state->height);
            func_0806FFF8(state->second, state->second_buffer,
                         state->x, state->y, uncovered, state->height);
        }
        break;
    }

    func_0802AC14(state->panel, state->panel_buffer,
                 state->position, state->y, state->height);
    width = state->width;
    if (width + (s8)state->position > 30)
        width = (s8)width + 30 - (width + state->position);
    func_0802A370(state->position, state->y, width, state->height);
    func_08016800(state->tiles + (u16)((state->y << 5) + (s8)state->position),
                 width, state->height, 0x800, state->style, 13, 3, 11);
    return done;
}
