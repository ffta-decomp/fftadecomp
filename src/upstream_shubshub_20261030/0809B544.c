/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/0809B544.c
 * Original SHA-256: bcea90ff2835686a9395f6945f86b8d175da0fed6dcfe5cce78b3b6c88bdf41e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    void *unit;
    u32 unknown_04;
    s16 x;
    s16 height;
    s16 y;
    u8 unknown_0E[0x0d];
    u8 height_limit;
    u8 flags;
    u8 unknown_1D[0x1f];
    void *map;
} Actor0809B544;

typedef struct {
    u8 x;
    u8 y;
    u8 height;
    u8 unknown_03;
} Point0809B544;

typedef struct {
    Actor0809B544 *actor;
    Point0809B544 *points;
    u8 unknown_08[0x1f];
    u8 direction;
} Movement0809B544;

typedef struct {
    s16 x;
    s16 height;
    s16 y;
} Position0809B544;

extern u8 func_0801CC7C(u8 x, u8 y);
extern s32 func_08149384(void *map, u8 x, u8 y);
extern s32 func_081493AC(void *map, u8 x, u8 y);
extern u8 func_0801CC18(u8 x, u8 y);

static inline void set_direction(s32 direction, s8 *dx, s8 *dy)
{
    switch (direction) {
    case 0:
        *dx = 0;
        *dy = 1;
        break;
    case 1:
        *dx = -1;
        *dy = 0;
        break;
    case 2:
        *dx = 0;
        *dy = -1;
        break;
    case 3:
        *dx = 1;
        *dy = 0;
        break;
    default:
        *dx = 0;
        *dy = 0;
        break;
    }
}

/* Complete target [0x0809B544, 0x0809B6D0): 396 bytes, 188 instructions. */
u8 func_0809B544(void *state, u32 unused, u16 keys)
{
    Movement0809B544 *movement = state;
    Position0809B544 destination;
    s32 direction = -1;
    s8 dx, dy;

    if (keys & 0x20)
        direction = 1;
    if (keys & 0x10)
        direction = 3;
    if (keys & 0x40)
        direction = 2;
    if (keys & 0x80)
        direction = 0;
    if (direction < 0)
        return 0;

    set_direction(direction, &dx, &dy);
    movement->direction = direction;
    destination.x = (movement->actor->x >> 5) + dx;
    destination.y = (movement->actor->y >> 5) + dy;
    if (destination.x < 0 || destination.y < 0)
        return 0;
    if (!func_0801CC7C((u16)destination.x, (u16)destination.y))
        return 0;
    if (movement->actor->flags & 0x10) {
        if (!func_08149384(movement->actor->map,
                           (u16)destination.x, (u16)destination.y))
            return 0;
        if ((u8)func_081493AC(movement->actor->map,
                              (u16)destination.x, (u16)destination.y)
            > movement->actor->height_limit)
            return 0;
    }
    destination.height = func_0801CC18((u16)destination.x, (u16)destination.y);
    movement->points[0].x = movement->actor->x >> 5;
    movement->points[0].height = movement->actor->height >> 4;
    movement->points[0].y = movement->actor->y >> 5;
    movement->points[1].x = destination.x;
    movement->points[1].height = destination.height;
    movement->points[1].y = destination.y;
    return 1;
}
