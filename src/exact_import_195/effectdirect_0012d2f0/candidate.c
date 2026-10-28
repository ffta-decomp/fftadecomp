#include "interfaces.h"
u32 ScoreBattleEffectFeasibility(const struct UnitCoordinateView *actor,
    const struct UnitCoordinateView *target, u32 selector)
    __asm__("EffectDirect_0012D2F0");
u32 ScoreBattleEffectFeasibility(const struct UnitCoordinateView *actor,
    const struct UnitCoordinateView *target, u32 selector)
{
    const s8 *actor_coordinates = actor->coordinates;
    s32 actor_x = *actor_coordinates++;
    s32 actor_y = *actor_coordinates;
    u32 score;
    u32 target_state;
    if (QueryEffectFeasibility(actor, target, actor_x, actor_y,
            target->coordinates[0], target->coordinates[1],
            target->coordinates[2], selector) == 0)
        return 0;
    target_state = (u8)CheckEffectTargetState(target, selector);
    score = 100;
    if (target_state == 0)
        score = 0;
    return score;
}
