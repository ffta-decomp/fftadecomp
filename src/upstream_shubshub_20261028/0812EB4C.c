/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812EB4C.c
 * Original SHA-256: 6fc3dd15de8520358730569ff272b0d209b17fd041a0e8bddae6b8dce03a73ca
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0812EB4C..0x0812EBD0: 132 bytes. */
typedef struct {
    s8 target_x;
    s8 target_y;
    s8 tile_x;
    s8 tile_y;
    s16 x;
    s16 height;
    s16 y;
    s16 direction;
    void *map;
} PositionState;

extern s32 func_0809D6BC(s8 x, s8 y);
extern s32 func_08131BE0(void *map, s8 x, s8 y);

void func_0812EB4C(PositionState *state)
{
    s32 direction = func_0809D6BC(state->target_x - state->tile_x,
                                state->target_y - state->tile_y);
    state->x = state->tile_x * 32 + 16;
    state->y = state->tile_y * 32 + 16;
    state->height = func_08131BE0(state->map, state->tile_x, state->tile_y) * 16;
    if (direction >= 0)
        state->direction = direction;

    switch (state->direction) {
    case 0:
        state->y += 8;
        break;
    case 1:
        state->x -= 8;
        break;
    case 2:
        state->y -= 8;
        break;
    default:
        state->x += 8;
        break;
    }
}
