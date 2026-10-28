#include "interfaces.h"

/* Prefer the closest other actor; an equal distance uses the original coin flip. */
u32 ChooseBattleDirection(struct BattleChoiceContext *choice, u8 x, u8 y)
{
    u16 minimum_distance = 256;
    u8 direction = (s16)ReadRandomValue() % 4;
    s32 index;
    for (index = 0; index < choice->count_12; index++) {
        struct ChoiceOwner *actor = choice->group_0c[index];
        if (actor != choice->owner) {
            struct ChoiceUnit *unit = actor->unit;
            s32 horizontal = unit->x - x;
            s32 vertical;
            s16 distance;
            if (horizontal < 0) horizontal = -horizontal;
            vertical = unit->y - y;
            if (vertical < 0) vertical = -vertical;
            distance = horizontal + vertical;
            if ((s16)distance > (s16)minimum_distance) continue;
            if ((s16)distance == (s16)minimum_distance &&
                ((u16)ReadRandomValue() % 2)) continue;
            minimum_distance = distance;
            {
                struct ChoiceUnit *selected_unit = actor->unit;
                direction = DirectionFromCoordinateDelta((s8)(selected_unit->x - x),
                                                         (s8)(selected_unit->y - y));
            }
        }
    }
    return direction;
}
