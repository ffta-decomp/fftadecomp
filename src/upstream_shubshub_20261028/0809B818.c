/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0809B818.c
 * Original SHA-256: 1486d5f28da7627d538a6e8730923b7dcb7d7672b76eb34af169e9d1e82371d1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0809B818..0x0809B88A: 114 bytes. */
typedef struct {
    void *unit;
} UnitOwner;

typedef struct {
    u8 x;
    u8 y;
    u16 unknown_02;
} PathPoint;

typedef struct {
    UnitOwner *owner;
    PathPoint *points;
    u8 unknown_08[8];
    s16 x;
    s16 height;
    s16 y;
    u16 unknown_16;
    s16 index;
    u8 unknown_1A[0xC2];
    u16 timer;
} MovementState;

u8 *func_080C7EA4(void *unit, u32 selector);
s32 func_08099C1C(UnitOwner *owner, s8 x, s8 y);

static inline u8 unit_is_ready(UnitOwner *owner)
{
    if (*func_080C7EA4(owner->unit, 0x44) == 3)
        return 1;
    return 0;
}

void func_0809B818(MovementState *state)
{
    if (unit_is_ready(state->owner)) {
        state->x = state->points[state->index - 1].x * 32 + 16;
        state->height = func_08099C1C(state->owner,
                                    (s8)state->points[state->index - 1].x,
                                    (s8)state->points[state->index - 1].y) * 16;
        state->y = state->points[state->index - 1].y * 32 + 16;
        state->timer = 10;
    }
}
