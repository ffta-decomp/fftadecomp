#include "pending_area.h"

u32 HasPendingEffectInTargetArea(Actor *actor, u8 target_x, u8 target_y,
                               u16 action, u16 slot)
{
    TargetRequest request;
    CandidatePoint *points = AllocateScratch(4096);
    s32 delta_x,delta_y;
    u32 direction;
    s32 count,index;
    CandidatePoint *point;
    Actor *target;

    request.unit = actor->unit;
    request.source_x = actor->x >> 5;
    request.source_y = actor->y >> 5;
    request.action = action;
    request.slot = slot;
    request.target_x = target_x;
    request.target_y = target_y;
    delta_x = (s8)(target_x - request.source_x);
    delta_y = (s8)(target_y - request.source_y);
    direction = (u8)DirectionFromDelta(delta_x,delta_y);
    if ((s8)direction < 0)
        direction = actor->direction;
    count = CollectTargetPoints(&request,(s8)direction,1,points);
    if (count > 0) {
        index = 0;
        for (;index < count;index++) {
            target = FindTargetAt(actor->workspace,points[index].x,points[index].y);
            if (target) {
                if ((u8)HasPendingEffect(actor->unit,target->unit,slot,action)==1)
                    goto accepted;
            }
        }
        FreeScratch(points);
        return 0;
    }
accepted:
    FreeScratch(points);
    return 1;
}
