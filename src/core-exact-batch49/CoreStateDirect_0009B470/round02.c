#include "interfaces.h"
/* Route coordinates are reloaded after the facing write; no copied-point snapshot. */
u32 PrepareNextBattleRouteStep(struct BattleRouteRecord *record)
    asm("CoreStateDirect_0009B470");
u32 PrepareNextBattleRouteStep(struct BattleRouteRecord *record)
{
    int ordinal;
    struct RoutePoint *current;
    struct RoutePoint *next;
    int dx, dy, height_delta;
    int distance;
    u32 facing;
    u8 current_x, next_x;
    ordinal = record->index;
    if (ordinal >= record->count - 1)
        return 0;
    current = &record->route[ordinal];
    next = &record->route[ordinal + 1];
    dx = next->x - current->x;
    dy = next->y - current->y;
    if (dx > 0)
        facing = 3;
    else if (dx < 0)
        facing = 1;
    else if (dy > 0)
        facing = 0;
    else
        facing = dy < 0 ? 2 : 0;
    record->facing = facing;
    next_x = next->x;
    current_x = current->x;
    height_delta = next->z - current->z;
    dy = next->y - current->y;
    record->start_x = current_x * 32 + 16;
    record->start_z = current->z * 16;
    record->start_y = current->y * 32 + 16;
    record->target_x = next->x * 32 + 16;
    record->target_z = next->z * 16;
    record->target_y = next->y * 32 + 16;
    dx = next_x - current_x;
    distance = __builtin_abs(dx) + __builtin_abs(dy);
    if (distance > 1) {
        if (height_delta != 0)
            return 5;
        return 4;
    }
    if (height_delta == 1)
        return 2;
    if (height_delta > 1)
        return 6;
    if (height_delta == -1)
        return 3;
    if (height_delta < -1)
        return 7;
    return 1;
}
