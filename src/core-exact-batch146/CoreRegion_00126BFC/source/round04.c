#include "contract.h"
/* The phase100 flag branch retains this initialized actor snapshot in R4. */
static __inline__ struct SceneActor *CaptureActorForFlagBranch(struct SceneActor *actor)
{
    register struct SceneActor *snapshot __asm__("r4")=actor;
    asm("" : "+r"(snapshot));
    return snapshot;
}
u32 ProcessSceneActorDirectionTransition(TaskNode *unused_task,
    struct DirectionEvent *event,struct DirectionState *state)
{
    struct SceneUnit *unit;
    struct SceneActor *actor;
    struct SceneActor *flag_actor;
    u32 mode;
    u32 original_direction,target_direction;
    s32 difference;
    switch(event->phase) {
    case 0:
        unit=ResolveSceneUnit((u8)event->unit_selector);
        state->owner=event->owner;
        state->actor=FindPrimaryActor(GetBattleActionRegistry(),unit);
        original_direction=unit->direction;
        state->current=original_direction;
        target_direction=event->target;
        state->target=target_direction;
        state->counter=6;
        state->mode=event->mode;
        if ((original_direction<<24)>(target_direction<<24)) {
            difference=state->current-state->target;
            state->current--;
        } else {
            difference=state->target-state->current;
            state->current++;
        }
        if(difference!=2)state->current=state->target;
        mode=state->mode;
        actor=state->actor;
        if(mode==0 || (actor->flags&4)!=0) {
            ApplyBattleActorState(actor,1,(s8)state->current,0);
            state->actor->unit->direction=state->current;
            ReapplySceneActorDirection(state->actor,0,state->current);
        } else {
            ReapplySceneActorDirection(actor,1,state->current);
        }
        break;
    case 1:
        break;
    case 0x100:
        if(state->counter!=0) {
            state->counter--;
            break;
        }
        if(state->current!=state->target) {
            mode=state->mode;
            actor=state->actor;
            if(mode==0 || ((flag_actor=CaptureActorForFlagBranch(actor))->flags&4)!=0) {
                ApplyBattleActorState(actor,1,(s8)state->target,0);
                state->actor->unit->direction=state->target;
                ReapplySceneActorDirection(state->actor,0,state->target);
            } else {
                ReapplySceneActorDirection(flag_actor,1,state->target);
            }
            state->current=state->target;
            state->counter=6;
        } else {
            event->phase=0x101;
        }
        break;
    case 0x101:
        state->owner->complete=1;
        event->phase=3;
        break;
    }
    return 0;
}
asm(".global ResolveSceneUnit\n.thumb_set ResolveSceneUnit,0x08125579\n"
    ".global GetBattleActionRegistry\n.thumb_set GetBattleActionRegistry,0x08096d7d\n"
    ".global FindPrimaryActor\n.thumb_set FindPrimaryActor,0x08099561\n"
    ".global ApplyBattleActorState\n.thumb_set ApplyBattleActorState,0x0809836d\n"
    ".global ReapplySceneActorDirection\n.thumb_set ReapplySceneActorDirection,0x08124711\n");
