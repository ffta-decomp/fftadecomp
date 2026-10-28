#include "interfaces.h"

void InitializeBattleDirectionChoice(void *node, direction_s32 x,
    direction_s32 height, direction_s32 y, direction_s32 direction)
{
    InitializeDirectionChoiceObject((volatile DirectionChoiceObject *)0x0200f8a8,
        node, (direction_s16)x, (direction_s16)height, (direction_s16)y,
        (direction_s8)direction);
}
